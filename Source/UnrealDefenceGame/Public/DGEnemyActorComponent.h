// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DGEnemyActorComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPIsZeroDelegate);
DECLARE_MULTICAST_DELEGATE(FOnHPChangedDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALDEFENCEGAME_API UDGEnemyActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDGEnemyActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void InitializeComponent() override;

	FOnHPIsZeroDelegate OnHPIsZero;					//HP가 0이 되었을 떄의 델리게이트
	FOnHPChangedDelegate OnHPChanged;				//HP가 변동될 때의 델리게이트

	void SetNewNum(int32 NewNum);
	void SetDamage(float NewDamage);
	void SetHP(float NewHP);
	float GetHPRatio() const;
	float GetSpeed() const { return Speed; }
	int GetAttack() const { return Attack; }
	int32 GetGold() const{ return Gold; }
	
private:
	struct FEnemyStatData* CurrentStatData = nullptr;
	UPROPERTY(Transient, EditInstanceOnly, Category = "Stat", Meta = (AllowPrivateAccess = true))
	int32 Level;
	UPROPERTY(Transient, EditInstanceOnly, Category = "Stat", Meta = (AllowPrivateAccess = true))
	float MaxHP;
	UPROPERTY(Transient, EditInstanceOnly, Category = "Stat", Meta = (AllowPrivateAccess = true))
	float CurrentHP;
	UPROPERTY(Transient, EditInstanceOnly, Category = "Stat", Meta = (AllowPrivateAccess = true))
	float Speed;
	UPROPERTY(Transient, EditInstanceOnly, Category = "Stat", Meta = (AllowPrivateAccess = true))
	int32 Attack;
	UPROPERTY(Transient, EditInstanceOnly, Category = "Stat", Meta = (AllowPrivateAccess = true))
	int32 Gold;

	float TempSpeed = 0.0f;
	int32 TempGold = 0;

	void SetAddStatAtEnemy();
};
