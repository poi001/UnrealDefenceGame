// Fill out your copyright notice in the Description page of Project Settings.


#include "DGCameraPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "DGPlayerController.h"
#include "Editor/EditorEngine.h"
#include "DGGameStateBase.h"

// Sets default values
ADGCameraPawn::ADGCameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("SCENE"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	RootComponent = RootScene;
	SpringArm->SetupAttachment(RootScene);
	Camera->SetupAttachment(SpringArm);

	SpringArm->TargetArmLength = 1200.0f;
	SpringArm->SetRelativeRotation(FRotator(-70.0f, 0.0f, 0.0f));
	SpringArm->bDoCollisionTest = false;

	CamSpeed = 10.0f;
	StartLocation = FVector(-40.0f, -240.0f, 292.0f);
	Margine = 50.0f;
}

// Called when the game starts or when spawned
void ADGCameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
	DGPlayerController = Cast<ADGPlayerController>(GetController());
}

// Called every frame
void ADGCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (DGPlayerController->bIsGameMode)
	{
		AddActorWorldOffset(GetCameraPanningDirection() * CamSpeed);
	}

	auto DGGameStateBase = Cast<ADGGameStateBase>(GetWorld()->GetGameState());
	DGGameStateBase->Time = GetWorld()->GetUnpausedTimeSeconds();
	DGGameStateBase->OnTick.Broadcast();
}

// Called to bind functionality to input
void ADGCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("StartLocation"), EInputEvent::IE_Pressed, this, &ADGCameraPawn::OnClickedStartLocation);
}

void ADGCameraPawn::OnClickedStartLocation()
{
	SetActorLocation(StartLocation);
}

FVector ADGCameraPawn::GetCameraPanningDirection()
{
	float MousePosX = 0.0f;
	float MousePosY = 0.0f;
	float CamDitectionX = 0.0f;
	float CamDitectionY = 0.0f;

	DGPlayerController->GetViewportSize(ScreenSizeX, ScreenSizeY);
	DGPlayerController->GetMousePosition(MousePosX, MousePosY);		//윈도우 좌표계

	if (MousePosX <= Margine)					//Left
	{
		CamDitectionY = -1.0f;
	}
	if (MousePosY <= Margine)					//Down
	{
		CamDitectionX = 1.0f;
	}
	if (MousePosX >= ScreenSizeX - Margine)		//Right
	{
		CamDitectionY = 1.0f;
	}
	if (MousePosY >= ScreenSizeY - Margine)		//Up
	{
		CamDitectionX = -1.0f;
	}

	return FVector(CamDitectionX, CamDitectionY, 0.0f);
}