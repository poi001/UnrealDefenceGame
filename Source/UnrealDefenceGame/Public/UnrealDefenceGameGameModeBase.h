// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UnrealDefenceGameGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class UNREALDEFENCEGAME_API AUnrealDefenceGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AUnrealDefenceGameGameModeBase();

	virtual void PostLogin(APlayerController* NewController) override;
};
