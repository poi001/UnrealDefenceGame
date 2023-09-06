// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DGEnemyHPBarWidget.generated.h"

/**
 * 
 */
UCLASS(Meta = (DisableNativeTick))
class UNREALDEFENCEGAME_API UDGEnemyHPBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(Meta = (BindWidget))
	class UProgressBar* PB_HPBar;

public:
	void UpdateHPBar();
	void BindEnemyStat(class UDGEnemyActorComponent* NewEnemyStat);

private:
	TWeakObjectPtr<class UDGEnemyActorComponent> CurrentEnemyStat;
};
