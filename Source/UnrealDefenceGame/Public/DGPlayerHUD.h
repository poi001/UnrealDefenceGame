// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DGPlayerHUD.generated.h"

/**
 * 
 */
UCLASS(Meta = (DisableNativeTick))
class UNREALDEFENCEGAME_API UDGPlayerHUD : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(Meta = (BindWidget))
	class UTextBlock* Text_Life;
	UPROPERTY(Meta = (BindWidget))
	class UTextBlock* Text_Gold;
	UPROPERTY(Meta = (BindWidget))
	class UTextBlock* Text_PlusDamage;
	UPROPERTY(Meta = (BindWidget))
	class UTextBlock* Text_PlusGold;
	UPROPERTY(Meta = (BindWidget))
	class UTextBlock* Text_PlusSlow;
	UPROPERTY(Meta = (BindWidget))
	class UTextBlock* Text_PlusAttackSpeed;
	UPROPERTY(Meta = (BindWidget))
	class UTextBlock* Text_Time;
	UPROPERTY(Meta = (BindWidget))
	class UTextBlock* Text_Level;

	UPROPERTY()
	class ADGGameStateBase* DGGameStateBase;

public:
	void SetHUDText();
	void SetTime();
};
