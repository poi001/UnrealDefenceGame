// Copyright Epic Games, Inc. All Rights Reserved.


#include "UnrealDefenceGameGameModeBase.h"
#include "DGCameraPawn.h"
#include "DGPlayerController.h"
#include "DGGameStateBase.h"


AUnrealDefenceGameGameModeBase::AUnrealDefenceGameGameModeBase()
{
	ConstructorHelpers::FClassFinder<ADGCameraPawn>CameraPawn(TEXT("/Game/Actor/Camera/MyDGCameraPawn.MyDGCameraPawn_C"));
	if(CameraPawn.Succeeded()) DefaultPawnClass = CameraPawn.Class;
	PlayerControllerClass = ADGPlayerController::StaticClass();
	GameStateClass = ADGGameStateBase::StaticClass();
}

void AUnrealDefenceGameGameModeBase::PostLogin(APlayerController* NewController)
{
	Super::PostLogin(NewController);

}