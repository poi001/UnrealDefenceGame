// Fill out your copyright notice in the Description page of Project Settings.


#include "DGEnemyAnimInstance.h"
#include "DGEnemyCharacter.h"


UDGEnemyAnimInstance::UDGEnemyAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
	IsDead = false;
}

void UDGEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	//Pawn에 폰의 권한을 줌
	auto Pawn = TryGetPawnOwner();
	if (!::IsValid(Pawn)) return;

	//캐릭터가 죽지 않았을 때는 캐릭터의 스피드 변수에 값을 기입한다. 
	if (!IsDead)
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
	}
}