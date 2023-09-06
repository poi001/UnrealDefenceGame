// Fill out your copyright notice in the Description page of Project Settings.


#include "DGTowerActorComponent.h"
#include "DGGameStateBase.h"
#include "DGGameInstance.h"

// Sets default values for this component's properties
UDGTowerActorComponent::UDGTowerActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Level = 1;
}


// Called when the game starts
void UDGTowerActorComponent::BeginPlay()
{
	Super::BeginPlay();

	DGGameStateBase = Cast<ADGGameStateBase>(GetWorld()->GetGameState());
	DGGameStateBase->OnChangePlayerStatDelegate.AddUObject(this, &UDGTowerActorComponent::SetAddStatAtTower);
}

void UDGTowerActorComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	SetAddTypeAtGameStatBase(false);
	DGGameStateBase->OnChangePlayerStatDelegate.Broadcast();
	DGGameStateBase->OnChangePlayerStatDelegate.RemoveAll(this);
}


// Called every frame
void UDGTowerActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UDGTowerActorComponent::SetNewLevelAndType(int32 NewLevel, ETowerColor NewTowerType)
{
	auto DGGameInstance = Cast<UDGGameInstance>(GetWorld()->GetGameInstance());
	CurrentStatData = DGGameInstance->GetTowerDataTable(NewTowerType, NewLevel);
	if (CurrentStatData != nullptr)
	{
		Level = NewLevel;
		BasicAD = CurrentStatData->AD;
		BasicAS = CurrentStatData->AS;
		AR = CurrentStatData->AR;
		AB = CurrentStatData->AB;
		Gold = CurrentStatData->Gold;

		TowerColor = NewTowerType;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("DGTowerActorComponent's DGGameInstance is nullptr"));
	}

	SetAddTypeAtGameStatBase(true);
	SetAddStatAtTower();
	DGGameStateBase->OnChangePlayerStatDelegate.Broadcast();
}
void UDGTowerActorComponent::SetAddStatAtTower()
{
	FinalAD = BasicAD + BasicAD * DGGameStateBase->PlusDamage;
	FinalAS = BasicAS + BasicAS * DGGameStateBase->PlusAS;
}
void UDGTowerActorComponent::SetAddTypeAtGameStatBase(bool IsItPositiveNumber)
{
	switch (TowerColor)
	{
	case ETowerColor::Red: {
		if (IsItPositiveNumber) DGGameStateBase->PlusDamage += AB;
		else DGGameStateBase->PlusDamage -= AB;
		}
		 break;
	case ETowerColor::Yellow: {
		if (IsItPositiveNumber) DGGameStateBase->PlusGold += AB;
		else DGGameStateBase->PlusGold -= AB;
		}
		break;
	case ETowerColor::Green: {
		if (IsItPositiveNumber) DGGameStateBase->PlusSlow += AB;
		else DGGameStateBase->PlusSlow -= AB;
		}
		break;
	case ETowerColor::Blue: {
		if (IsItPositiveNumber) DGGameStateBase->PlusAS += AB;
		else DGGameStateBase->PlusAS -= AB;
		}
		break;
	default:
		break;
	}
}