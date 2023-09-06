// Fill out your copyright notice in the Description page of Project Settings.


#include "DGPlayerHUD.h"
#include "DGGameStateBase.h"
#include "Components/TextBlock.h"


void UDGPlayerHUD::NativeConstruct()
{
	Text_Life = Cast<UTextBlock>(GetWidgetFromName(FName("Text_Life")));
	Text_Gold = Cast<UTextBlock>(GetWidgetFromName(FName("Text_Gold")));
	Text_PlusDamage = Cast<UTextBlock>(GetWidgetFromName(FName("Text_PlusDamage")));
	Text_PlusGold = Cast<UTextBlock>(GetWidgetFromName(FName("Text_PlusGold")));
	Text_PlusSlow = Cast<UTextBlock>(GetWidgetFromName(FName("Text_PlusSlow")));
	Text_PlusAttackSpeed = Cast<UTextBlock>(GetWidgetFromName(FName("Text_PlusAttackSpeed")));
	Text_Time = Cast<UTextBlock>(GetWidgetFromName(FName("Text_Time")));
	Text_Level = Cast<UTextBlock>(GetWidgetFromName(FName("Text_Level")));

	if (Text_Life == nullptr) GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Text_Life is nullptr"));
	if (Text_Gold == nullptr) GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Text_Gold is nullptr"));
	if (Text_PlusDamage == nullptr) GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Text_PlusDamage is nullptr"));
	if (Text_PlusGold == nullptr) GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Text_PlusGold is nullptr"));
	if (Text_PlusSlow == nullptr) GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Text_PlusSlow is nullptr"));
	if (Text_PlusAttackSpeed == nullptr) GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Text_PlusAttackSpeed is nullptr"));
	if (Text_Time == nullptr) GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Text_Time is nullptr"));
	if (Text_Level == nullptr) GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Text_Level is nullptr"));

	DGGameStateBase = Cast<ADGGameStateBase>(GetWorld()->GetGameState());
	DGGameStateBase->OnChangePlayerStatDelegate.AddUObject(this, &UDGPlayerHUD::SetHUDText);
	DGGameStateBase->OnTick.AddUObject(this, &UDGPlayerHUD::SetTime);
}

void UDGPlayerHUD::SetHUDText()
{
	Text_Life->SetText(FText::FromString(FString::FromInt(DGGameStateBase->PlayerLife)));
	Text_Gold->SetText(FText::FromString(FString::FromInt(DGGameStateBase->PlayerGold)));
	Text_PlusDamage->SetText(FText::FromString(FString::Printf(TEXT("+%.2f%%"), DGGameStateBase->PlusDamage)));
	Text_PlusGold->SetText(FText::FromString(FString::Printf(TEXT("+%dG"), DGGameStateBase->PlusGold)));
	Text_PlusSlow->SetText(FText::FromString(FString::Printf(TEXT("+%.2f%%"), DGGameStateBase->PlusSlow)));
	Text_PlusAttackSpeed->SetText(FText::FromString(FString::Printf(TEXT("+%.2f%%"), DGGameStateBase->PlusAS)));
	Text_Level->SetText(FText::FromString(FString::Printf(TEXT("Level: %d"), DGGameStateBase->CurrentLevel)));
}

void UDGPlayerHUD::SetTime()
{
	int32 Seconds = 0;
	int32 Minutes = 0;
	Minutes = static_cast<int32>(DGGameStateBase->Time) / 60;
	Seconds = static_cast<int32>(DGGameStateBase->Time) % 60;
	if (Minutes >= 10)
	{
		if (Seconds >= 10) Text_Time->SetText(FText::FromString(FString::Printf(TEXT("%d:%d"), Minutes, Seconds)));
		else Text_Time->SetText(FText::FromString(FString::Printf(TEXT("%d:0%d"), Minutes, Seconds)));
	}
	else
	{
		if (Seconds >= 10) Text_Time->SetText(FText::FromString(FString::Printf(TEXT("0%d:%d"), Minutes, Seconds)));
		else Text_Time->SetText(FText::FromString(FString::Printf(TEXT("0%d:0%d"), Minutes, Seconds)));
	}

	if (DGGameStateBase->CurrentLevel != Minutes + 1)
	{
		if (Minutes > 9) DGGameStateBase->OnGameClear.Broadcast();
		else
		{
			DGGameStateBase->CurrentLevel = Minutes + 1;
			SetHUDText();
		}
	}
}