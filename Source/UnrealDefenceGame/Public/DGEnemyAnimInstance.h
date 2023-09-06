// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "DGEnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREALDEFENCEGAME_API UDGEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UDGEnemyAnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn)
	float CurrentPawnSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn)
	bool IsDead;
};
