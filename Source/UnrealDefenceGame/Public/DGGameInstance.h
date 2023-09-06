// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UnrealDefenceGame.h"
#include "Engine/DataTable.h"			//데이터 테이블 헤더파일 추가
#include "Engine/StreamableManager.h"	//FStreamableManager 헤더파일
#include "Engine/GameInstance.h"
#include "DGGameInstance.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FEnemyStatData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FEnemyStatData() : Level(1), HP(100.0f), Speed(50.0f), Attack(1), Gold(10) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float HP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Attack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Gold;


};

USTRUCT(BlueprintType)
struct FTowerStatData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FTowerStatData() : Level(1), AD(100.0f), AS(1.0f), AR(64), AB(1.0f), Gold(100) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float AD;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float AS;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float AR;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float AB;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Gold;
};

UCLASS()
class UNREALDEFENCEGAME_API UDGGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UDGGameInstance();

	FEnemyStatData* GetEnemyStatTable(int32 Level);
	FTowerStatData* GetTowerDataTable(ETowerColor TowerColor, int32 Level);

	FStreamableManager StreamableManager;

private:
	UPROPERTY()
	class UDataTable* EnemyStatTable;
	UPROPERTY()
	class UDataTable* TowerDataTable_Red;
	UPROPERTY()
	class UDataTable* TowerDataTable_Yellow;
	UPROPERTY()
	class UDataTable* TowerDataTable_Green;
	UPROPERTY()
	class UDataTable* TowerDataTable_Blue;
	UPROPERTY()
	class UDataTable* TowerDataTable_Black;
};
