// Fill out your copyright notice in the Description page of Project Settings.


#include "DGTowerWidget.h"
#include "DGGameStateBase.h"
#include "DGPlayerController.h"
#include "DGTowerActor.h"
#include "DGTowerActorComponent.h"
#include "DGTileActor.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Math/RandomStream.h"


void UDGTowerWidget::NativeConstruct()
{
	DGGameStateBase = Cast<ADGGameStateBase>(GetWorld()->GetGameState());
	DGGameStateBase->OnChangePlayerStatDelegate.AddUObject(this, &UDGTowerWidget::SetTowerWidgetText);
	DGGameStateBase->OnChangePlayerStatDelegate.AddUObject(this, &UDGTowerWidget::SetButtonEnable);
	DGPlayerController = Cast<ADGPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void UDGTowerWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Text_Sell = Cast<UTextBlock>(GetWidgetFromName(FName("Text_Sell")));
	Text_Upgrade = Cast<UTextBlock>(GetWidgetFromName(FName("Text_Upgrade")));

	if (Text_Sell == nullptr) GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("Text_Sell is nullptr"));
	if (Text_Upgrade == nullptr) GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("Text_Upgrade is nullptr"));

	Button_Buy = Cast<UButton>(GetWidgetFromName(FName("Button_Buy")));
	Button_Sell = Cast<UButton>(GetWidgetFromName(FName("Button_Sell")));
	Button_Upgrade = Cast<UButton>(GetWidgetFromName(FName("Button_Upgrade")));
	Button_Exit = Cast<UButton>(GetWidgetFromName(FName("Button_Exit")));

	if (Button_Buy != nullptr) Button_Buy->OnClicked.AddDynamic(this, &UDGTowerWidget::OnClickedBuyButton);
	if (Button_Sell != nullptr) Button_Sell->OnClicked.AddDynamic(this, &UDGTowerWidget::OnClickedSellButton);
	if (Button_Upgrade != nullptr) Button_Upgrade->OnClicked.AddDynamic(this, &UDGTowerWidget::OnClickedUpgradeButton);
	if (Button_Exit != nullptr) Button_Exit->OnClicked.AddDynamic(this, &UDGTowerWidget::OnClickedExitButton);
}

void UDGTowerWidget::NativeDestruct()
{
	Super::NativeDestruct();

	DGTileActor = nullptr;
	DGGameStateBase->OnChangePlayerStatDelegate.RemoveAll(this);
}

void UDGTowerWidget::OnClickedBuyButton()
{
	FRandomStream RandomStream;
	RandomStream.GenerateNewSeed();
	ETowerColor RandTowerColor = static_cast<ETowerColor>(RandomStream.RandRange(0, TOWERCOLORNUM - 1));

	DGTileActor->SpawnTowerActor();
	if (DGTileActor->DGTowerActor.IsValid())
	{
		DGTileActor->DGTowerActor->InitializeTower(1, RandTowerColor);
		DGTileActor->IsOn = true;
		SetGold(-100);
	}
	SetTowerWidgetText();

	DGPlayerController->CloseTowerWidget();
}
void UDGTowerWidget::OnClickedSellButton()
{
	if (DGTileActor->DGTowerActor.IsValid())
	{
		SetGold(DGTileActor->DGTowerActor->TowerStatComponent->GetGold());
		DGTileActor->DGTowerActor->Destroy();
		DGTileActor->IsOn = false;
	}
	SetTowerWidgetText();

	DGPlayerController->CloseTowerWidget();
}
void UDGTowerWidget::OnClickedUpgradeButton()
{
	if (DGTileActor->DGTowerActor.IsValid())
	{
		int32 Cost = (DGTileActor->DGTowerActor->TowerStatComponent->GetLevel() * 100) * -1;
		int32 TowerLevel = DGTileActor->DGTowerActor->Level + 1;
		ETowerColor TowerColor = DGTileActor->DGTowerActor->Color;

		SetGold(Cost);
		DGTileActor->DGTowerActor->InitializeTower(TowerLevel, TowerColor);
	}
	SetTowerWidgetText();

	DGPlayerController->CloseTowerWidget();
}
void UDGTowerWidget::OnClickedExitButton()
{
	DGPlayerController->CloseTowerWidget();
}

void UDGTowerWidget::SetTowerWidgetText()
{
	if (DGTileActor.IsValid() && DGTileActor->IsOn)
	{
		if (DGTileActor->DGTowerActor.IsValid())
		{
			FString SellButtonString = 
				FString::Printf(TEXT("판매(+%dG)"), DGTileActor->DGTowerActor->TowerStatComponent->GetGold());
			FString UpgradeButtonString = 
				FString::Printf(TEXT("업그레이드(-%dG)"), DGTileActor->DGTowerActor->TowerStatComponent->GetLevel() * 100);
			Text_Sell->SetText(FText::FromString(*SellButtonString));
			Text_Upgrade->SetText(FText::FromString(*UpgradeButtonString));
		}
	}
	else
	{
		FString SellButtonString = TEXT("판매");
		FString UpgradeButtonString = TEXT("업그레이드");
		Text_Sell->SetText(FText::FromString(*SellButtonString));
		Text_Upgrade->SetText(FText::FromString(*UpgradeButtonString));
	}
}
void UDGTowerWidget::SetButtonEnable()
{
	Button_Buy->SetIsEnabled(false);
	Button_Sell->SetIsEnabled(false);
	Button_Upgrade->SetIsEnabled(false);

	if (DGTileActor.IsValid())
	{
		if (DGTileActor->IsOn)
		{
			Button_Buy->SetIsEnabled(false);

			Button_Sell->SetIsEnabled(true);

			if (DGGameStateBase->PlayerGold >= DGTileActor->DGTowerActor->TowerStatComponent->GetLevel() * 100)
			{
				if (DGTileActor->DGTowerActor->TowerStatComponent->GetLevel() < 3)
				{
					Button_Upgrade->SetIsEnabled(true);
				}
			}
		}
		else
		{
			if (DGGameStateBase->PlayerGold >= 100)
			{
				Button_Buy->SetIsEnabled(true);
			}
			else
			{
				Button_Buy->SetIsEnabled(false);
			}

			Button_Sell->SetIsEnabled(false);

			Button_Upgrade->SetIsEnabled(false);
		}
	}
}
void UDGTowerWidget::SetTileReference(TWeakObjectPtr<ADGTileActor> NewTileRef)
{
	if (NewTileRef.IsValid()) DGTileActor = NewTileRef;
	if (DGGameStateBase) DGGameStateBase->OnChangePlayerStatDelegate.Broadcast();
}
void UDGTowerWidget::SetGold(int32 AddGold)
{
	if (DGGameStateBase)
	{
		DGGameStateBase->PlayerGold += AddGold;
		DGGameStateBase->OnChangePlayerStatDelegate.Broadcast();
	}
}