// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DGEnemyCharacter.generated.h"

UCLASS()
class UNREALDEFENCEGAME_API ADGEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADGEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PostInitializeComponents() override;

	// 대미지를 받을 때, 처리하는 가상 함수
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator,
		AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable)
	void SetEnemyStat(int32 Level);
	UFUNCTION(BlueprintCallable)
	void OnOverlappedGoalActor();
	
	UDGEnemyActorComponent* GetEnemyStat()const { return DGEnemyStat; };

private:
	UPROPERTY()
	class UWidgetComponent* DGEnemyHPWidget;
	UPROPERTY()
	class UDGEnemyAnimInstance* DGEnemyAnim;
	UPROPERTY()
	class ADGGameStateBase* DGGameStateBase;
	UPROPERTY()
	class UDGEnemyActorComponent* DGEnemyStat;
};
