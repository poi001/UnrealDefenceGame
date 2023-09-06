// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DGSetting.generated.h"

/**
 * 
 */
UCLASS(config=Setting)
class UNREALDEFENCEGAME_API UDGSetting : public UObject
{
	GENERATED_BODY()
	
public:
	UDGSetting();

	UPROPERTY(config)
	TArray<FSoftObjectPath> TowerMesh;
	UPROPERTY(config)
	TArray<FSoftObjectPath> TowerMaterialInstance;
};
