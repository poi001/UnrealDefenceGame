// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UnrealDefenceGame.h"
#include "Blueprint/UserWidget.h"
#include "DGTowerWidget.generated.h"

/**
 * 
 */
UCLASS(Meta = (DisableNativeTick))
class UNREALDEFENCEGAME_API UDGTowerWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;
	virtual void NativeDestruct() override;


	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Sell;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Upgrade;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Buy;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Sell;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Upgrade;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Exit;

	TWeakObjectPtr<class ADGTileActor> DGTileActor;
	UPROPERTY()
	class ADGGameStateBase* DGGameStateBase;
	UPROPERTY()
	class ADGPlayerController* DGPlayerController;


	UFUNCTION()
	void OnClickedBuyButton();
	UFUNCTION()
	void OnClickedSellButton();
	UFUNCTION()
	void OnClickedUpgradeButton();
	UFUNCTION()
	void OnClickedExitButton();

	void SetTowerWidgetText();
	void SetButtonEnable();
	void SetGold(int32 AddGold);

public:
	void SetTileReference(TWeakObjectPtr<class ADGTileActor> NewTileRef);
};
