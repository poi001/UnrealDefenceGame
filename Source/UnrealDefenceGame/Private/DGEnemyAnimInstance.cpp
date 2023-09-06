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

	//Pawn�� ���� ������ ��
	auto Pawn = TryGetPawnOwner();
	if (!::IsValid(Pawn)) return;

	//ĳ���Ͱ� ���� �ʾ��� ���� ĳ������ ���ǵ� ������ ���� �����Ѵ�. 
	if (!IsDead)
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
	}
}