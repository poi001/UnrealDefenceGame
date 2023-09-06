// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "DGGameStateBase.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnChangePlayerStatDelegate);
DECLARE_MULTICAST_DELEGATE(FOnPlayerLifeIsZero);
DECLARE_MULTICAST_DELEGATE(FOnTick);
DECLARE_MULTICAST_DELEGATE(FOnGameClear);

/**
 * 
 */
UCLASS()
class UNREALDEFENCEGAME_API ADGGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	ADGGameStateBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HUD")
	int32 PlayerGold;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HUD")
	int32 PlayerLife;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HUD")
	float PlusDamage;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HUD")
	int32 PlusGold;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HUD")
	float PlusSlow;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HUD")
	float PlusAS;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HUD")
	int32 CurrentLevel;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HUD")
	double Time;

	FOnChangePlayerStatDelegate OnChangePlayerStatDelegate;
	FOnPlayerLifeIsZero OnPlayerLifeIsZero;
	FOnTick OnTick;
	FOnGameClear OnGameClear;
};
