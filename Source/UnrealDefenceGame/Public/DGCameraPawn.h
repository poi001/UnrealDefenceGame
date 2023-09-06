// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DGCameraPawn.generated.h"

UCLASS()
class UNREALDEFENCEGAME_API ADGCameraPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADGCameraPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mouse")
	float CamSpeed;
	UPROPERTY()
	float Margine;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mouse")
	FVector StartLocation;

private:
	UPROPERTY()
	class USceneComponent* RootScene;
	UPROPERTY()
	class USpringArmComponent* SpringArm;
	UPROPERTY()
	class UCameraComponent* Camera;
	UPROPERTY()
	class ADGPlayerController* DGPlayerController;

	int32 ScreenSizeX;
	int32 ScreenSizeY;

	void OnClickedStartLocation();
	FVector GetCameraPanningDirection();
};
