// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DGPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALDEFENCEGAME_API ADGPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ADGPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;//temp

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UDGPlayerHUD> PlayerHUDWidgetClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UDGTowerWidget> TowerWidgetClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UUserWidget> GameOverWidgetClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UUserWidget> GameClearWidgetClass;

private:
	FInputModeGameOnly GameInputMode;		//���Ӹ��
	FInputModeUIOnly UIInputMode;			//UI���
	FInputModeGameAndUI GameAndUIInputMode;	//���ո��

	TWeakObjectPtr<class UDGPlayerHUD> PlayerHUDWidget;
	TWeakObjectPtr<class UDGTowerWidget> TowerWidget;
	TWeakObjectPtr<class UUserWidget> GameOverWidget;
	TWeakObjectPtr<class UUserWidget> GameClearWidget;

	TWeakObjectPtr<class ADGTileActor> DGTileActor;

public:
	bool bIsGameMode = false;

	void OpenTowerWidget(class ADGTileActor* SelectTile);
	void CloseTowerWidget();
	void OpenGameOverWidget();
	void OpenGameClearWidget();

	void SetInputModeGameOnly(bool IsGameMode);
};
