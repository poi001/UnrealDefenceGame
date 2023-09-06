// Fill out your copyright notice in the Description page of Project Settings.


#include "DGPlayerController.h"
#include "DGTowerWidget.h"
#include "DGPlayerHUD.h"
#include "DGTileActor.h"
#include "DGGameStateBase.h"
#include "Blueprint/UserWidget.h"


ADGPlayerController::ADGPlayerController()
{
	ConstructorHelpers::FClassFinder<UDGPlayerHUD>HUD_CLASS(TEXT("/Game/Widget/BP_PlayerHUD.BP_PlayerHUD_C"));
	if (HUD_CLASS.Succeeded()) PlayerHUDWidgetClass = HUD_CLASS.Class;
	ConstructorHelpers::FClassFinder<UDGTowerWidget>TOWERWIDGET_CLASS(TEXT("/Game/Widget/BP_TowerWidget.BP_TowerWidget_C"));
	if (TOWERWIDGET_CLASS.Succeeded()) TowerWidgetClass = TOWERWIDGET_CLASS.Class;
	ConstructorHelpers::FClassFinder<UUserWidget>GAMEOVERWIDGET_CLASS(TEXT("/Game/Widget/BP_GameOverWidget.BP_GameOverWidget_C"));
	if (GAMEOVERWIDGET_CLASS.Succeeded()) GameOverWidgetClass = GAMEOVERWIDGET_CLASS.Class;
	ConstructorHelpers::FClassFinder<UUserWidget>GAMECLEARWIDGET_CLASS(TEXT("/Game/Widget/BP_GameClearWidget.BP_GameClearWidget_C"));
	if (GAMECLEARWIDGET_CLASS.Succeeded()) GameClearWidgetClass = GAMECLEARWIDGET_CLASS.Class;

	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}

void ADGPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto DGGameStateBase = Cast<ADGGameStateBase>(GetWorld()->GetGameState());
	DGGameStateBase->OnPlayerLifeIsZero.AddUObject(this, &ADGPlayerController::OpenGameOverWidget);
	DGGameStateBase->OnGameClear.AddUObject(this, &ADGPlayerController::OpenGameClearWidget);

	SetInputModeGameOnly(true);

	PlayerHUDWidget = CreateWidget<UDGPlayerHUD>(GetWorld(), PlayerHUDWidgetClass);
	if (PlayerHUDWidget.IsValid())
	{
		PlayerHUDWidget->AddToViewport();
		PlayerHUDWidget->SetHUDText();
	}
	//TowerWidget = CreateWidget<UDGTowerWidget>(GetWorld(), TowerWidgetClass);
	//GameOverWidget = CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass);
	//GameClearWidget = CreateWidget<UUserWidget>(GetWorld(), GameClearWidgetClass);
}

void ADGPlayerController::OpenTowerWidget(ADGTileActor* SelectTile)
{
	TowerWidget = CreateWidget<UDGTowerWidget>(GetWorld(), TowerWidgetClass);
	SetInputModeGameOnly(false);
	if (TowerWidget.IsValid())
	{
		TowerWidget->AddToViewport();
		if (nullptr != SelectTile)
		{
			if (!DGTileActor.IsValid())
			{
				DGTileActor = SelectTile;
				SelectTile->IsSelecting = true;
				SelectTile->SetMaterialSelect();
				TowerWidget->SetTileReference(DGTileActor);
			}
			else UE_LOG(LogTemp, Error, TEXT("PlayerController->OpenTowerWidget->DGTileActor is Valid"));
		}
		else UE_LOG(LogTemp, Error, TEXT("PlayerController->OpenTowerWidget->SelectTile is nullptr"));
	}
	else UE_LOG(LogTemp, Error, TEXT("PlayerController->OpenTowerWidget->TowerWidget is not Valid"));
}
void ADGPlayerController::CloseTowerWidget()
{
	SetInputModeGameOnly(true);
	if (TowerWidget.IsValid())
	{
		TowerWidget->RemoveFromParent();
		if (DGTileActor.IsValid())
		{
			DGTileActor->IsSelecting = false;
			DGTileActor->SetMaterialBasic();
			DGTileActor = nullptr;
		}
		else UE_LOG(LogTemp, Error, TEXT("PlayerController->CloseTowerWidget->DGTileActor is not Valid"));
	}
	else UE_LOG(LogTemp, Error, TEXT("PlayerController->CloseTowerWidget->TowerWidget.IsNotValid"));
}

void ADGPlayerController::SetupInputComponent()//temp
{
	Super::SetupInputComponent();

	InputComponent->BindAction(TEXT("Temp"), EInputEvent::IE_Pressed, this, &ADGPlayerController::OpenGameOverWidget);
}
void ADGPlayerController::OpenGameOverWidget()
{
	GameOverWidget = CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass);
	Pause();
	GameOverWidget->AddToViewport();
	SetInputModeGameOnly(false);
}
void ADGPlayerController::OpenGameClearWidget()
{
	GameClearWidget = CreateWidget<UUserWidget>(GetWorld(), GameClearWidgetClass);
	Pause();
	GameClearWidget->AddToViewport();
	SetInputModeGameOnly(false);
}

void ADGPlayerController::SetInputModeGameOnly(bool IsGameMode)
{
	if (IsGameMode)
	{
		SetInputMode(GameInputMode);
		bIsGameMode = true;
	}
	else
	{
		SetInputMode(UIInputMode);
		bIsGameMode = false;
	}
}