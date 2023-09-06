// Fill out your copyright notice in the Description page of Project Settings.


#include "DGGameStateBase.h"


ADGGameStateBase::ADGGameStateBase()
{
	PlayerGold = 100;
	PlayerLife = 20;
	PlusDamage = 0.0f;
	PlusGold = 0;
	PlusSlow = 0.0f;
	PlusAS = 0.0f;
	CurrentLevel = 1;
	Time = 0.0f;
}