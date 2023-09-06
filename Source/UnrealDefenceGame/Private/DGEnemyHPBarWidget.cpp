// Fill out your copyright notice in the Description page of Project Settings.


#include "DGEnemyHPBarWidget.h"
#include "DGEnemyActorComponent.h"
#include "DGEnemyCharacter.h"
#include "Components/ProgressBar.h"


void UDGEnemyHPBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PB_HPBar = Cast<UProgressBar>(GetWidgetFromName(FName("PB_HPBar")));
	if (PB_HPBar == nullptr) UE_LOG(LogTemp, Error, TEXT("HPWidget is nullptr"));

	UpdateHPBar();
}

void UDGEnemyHPBarWidget::UpdateHPBar()
{
	if (CurrentEnemyStat.IsValid())
	{
		if (PB_HPBar != nullptr)
		{
			PB_HPBar->SetPercent(CurrentEnemyStat->GetHPRatio());
		}
	}
}

void UDGEnemyHPBarWidget::BindEnemyStat(class UDGEnemyActorComponent* NewEnemyStat)
{
	if (NewEnemyStat != nullptr)//temp
	{
		CurrentEnemyStat = NewEnemyStat;
		NewEnemyStat->OnHPChanged.AddUObject(this, &UDGEnemyHPBarWidget::UpdateHPBar);
	}
}