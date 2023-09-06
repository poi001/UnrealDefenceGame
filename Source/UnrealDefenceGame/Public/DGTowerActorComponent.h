// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UnrealDefenceGame.h"
#include "Components/ActorComponent.h"
#include "DGTowerActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALDEFENCEGAME_API UDGTowerActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDGTowerActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetNewLevelAndType(int32 NewLevel, ETowerColor NewTowerType);
	void SetAddStatAtTower();
	void SetAddTypeAtGameStatBase(bool IsItPositiveNumber);
	ETowerColor GetTowerType() const { return TowerColor; };
	int32 GetLevel() const{ return Level; };
	float GetAS() const { return FinalAS; };
	float GetAR() const { return AR; };
	float GetAD() const { return FinalAD; };
	int32 GetGold() const { return Gold; };
		
private:
	struct FTowerStatData* CurrentStatData = nullptr;
	UPROPERTY(Transient, EditInstanceOnly, Category = "Stat", Meta = (AllowPrivateAccess = true))
	int32 Level;
	UPROPERTY(Transient, EditInstanceOnly, Category = "Stat", Meta = (AllowPrivateAccess = true))
	float BasicAD;
	UPROPERTY(Transient, EditInstanceOnly, Category = "Stat", Meta = (AllowPrivateAccess = true))
	float FinalAD;
	UPROPERTY(Transient, EditInstanceOnly, Category = "Stat", Meta = (AllowPrivateAccess = true))
	float BasicAS;
	UPROPERTY(Transient, EditInstanceOnly, Category = "Stat", Meta = (AllowPrivateAccess = true))
	float FinalAS;
	UPROPERTY(Transient, EditInstanceOnly, Category = "Stat", Meta = (AllowPrivateAccess = true))
	float AR;
	UPROPERTY(Transient, EditInstanceOnly, Category = "Stat", Meta = (AllowPrivateAccess = true))
	float AB;
	UPROPERTY(Transient, EditInstanceOnly, Category = "Stat", Meta = (AllowPrivateAccess = true))
	int32 Gold;

	UPROPERTY()
	class ADGGameStateBase* DGGameStateBase;
	ETowerColor TowerColor = ETowerColor::Red;
};
