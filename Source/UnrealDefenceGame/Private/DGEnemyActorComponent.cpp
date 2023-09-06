// Fill out your copyright notice in the Description page of Project Settings.


#include "DGEnemyActorComponent.h"
#include "DGGameInstance.h"
#include "DGGameStateBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UDGEnemyActorComponent::UDGEnemyActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

	Level = 1;
}


// Called when the game starts
void UDGEnemyActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	auto DGGameStateBase = Cast<ADGGameStateBase>(GetWorld()->GetGameState());
	DGGameStateBase->OnChangePlayerStatDelegate.AddUObject(this, &UDGEnemyActorComponent::SetAddStatAtEnemy);

	SetNewNum(Level);
}

void UDGEnemyActorComponent::InitializeComponent()
{
	Super::InitializeComponent();

}

void UDGEnemyActorComponent::SetNewNum(int32 NewNum)
{
	auto DGGameInstance = Cast<UDGGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	CurrentStatData = DGGameInstance->GetEnemyStatTable(NewNum);
	if (CurrentStatData != nullptr)
	{
		Level = NewNum;
		MaxHP = CurrentStatData->HP;
		SetHP(CurrentStatData->HP);
		TempSpeed = CurrentStatData->Speed;
		Attack = CurrentStatData->Attack;
		TempGold = CurrentStatData->Gold;

		SetAddStatAtEnemy();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("DGEnemyActorComponent's DGGameInstance is nullptr"));
	}
}
void UDGEnemyActorComponent::SetDamage(float NewDamage)
{
	SetHP(FMath::Clamp<float>(CurrentHP - NewDamage, 0.0f, MaxHP));
}
void UDGEnemyActorComponent::SetHP(float NewHP)
{
	CurrentHP = NewHP;
	OnHPChanged.Broadcast();
	if (CurrentHP < KINDA_SMALL_NUMBER) //KINDA_SMALL_NUMBER은 미세한 오차범위를 조정해줄 매크로 ( 0이랑 비교할 때 )
	{
		CurrentHP = 0.0f;
		OnHPIsZero.Broadcast();
	}
}
float UDGEnemyActorComponent::GetHPRatio() const
{
	return (CurrentHP < KINDA_SMALL_NUMBER) ? 0.0f : (CurrentHP / MaxHP);
}

void UDGEnemyActorComponent::SetAddStatAtEnemy()
{
	auto DGGameStateBase = Cast<ADGGameStateBase>(GetWorld()->GetGameState());
	Speed = TempSpeed - TempSpeed * DGGameStateBase->PlusSlow;
	Gold = TempGold + DGGameStateBase->PlusGold;
}