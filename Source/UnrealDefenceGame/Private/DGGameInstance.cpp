// Fill out your copyright notice in the Description page of Project Settings.


#include "DGGameInstance.h"


UDGGameInstance::UDGGameInstance()
{
	ConstructorHelpers::FObjectFinder<UDataTable> DT_ENEMY(TEXT("/Game/Actor/Enemy/DataTable/EnemyStat_csv.EnemyStat_csv"));
	if (DT_ENEMY.Succeeded()) EnemyStatTable = DT_ENEMY.Object;

	ConstructorHelpers::FObjectFinder<UDataTable> DT_TOWER_RED(TEXT("/Game/Actor/Tower/csv/TowerStat_Red_csv.TowerStat_Red_csv"));
	if (DT_TOWER_RED.Succeeded()) TowerDataTable_Red = DT_TOWER_RED.Object;
	ConstructorHelpers::FObjectFinder<UDataTable> DT_TOWER_YELLOW(TEXT("/Game/Actor/Tower/csv/TowerStat_Yellow_csv.TowerStat_Yellow_csv"));
	if (DT_TOWER_YELLOW.Succeeded()) TowerDataTable_Yellow = DT_TOWER_YELLOW.Object;
	ConstructorHelpers::FObjectFinder<UDataTable> DT_TOWER_GREEN(TEXT("/Game/Actor/Tower/csv/TowerStat_Greencsv.TowerStat_Greencsv"));
	if (DT_TOWER_GREEN.Succeeded()) TowerDataTable_Green = DT_TOWER_GREEN.Object;
	ConstructorHelpers::FObjectFinder<UDataTable> DT_TOWER_BLUE(TEXT("/Game/Actor/Tower/csv/TowerStat_Blue_csv.TowerStat_Blue_csv"));
	if (DT_TOWER_BLUE.Succeeded()) TowerDataTable_Blue = DT_TOWER_BLUE.Object;
	ConstructorHelpers::FObjectFinder<UDataTable> DT_TOWER_BLACK(TEXT("/Game/Actor/Tower/csv/TowerStat_Black_csv.TowerStat_Black_csv"));
	if (DT_TOWER_BLACK.Succeeded()) TowerDataTable_Black = DT_TOWER_BLACK.Object;
}

FEnemyStatData* UDGGameInstance::GetEnemyStatTable(int32 Level)
{
	return EnemyStatTable->FindRow<FEnemyStatData>(*FString::FromInt(Level), TEXT(""));
}
FTowerStatData* UDGGameInstance::GetTowerDataTable(ETowerColor TowerColor, int32 Level)
{
	switch (TowerColor)
	{
	case ETowerColor::Red:
		return TowerDataTable_Red->FindRow<FTowerStatData>(*FString::FromInt(Level), TEXT(""));
		break;
	case ETowerColor::Yellow:
		return TowerDataTable_Yellow->FindRow<FTowerStatData>(*FString::FromInt(Level), TEXT(""));
		break;
	case ETowerColor::Green:
		return TowerDataTable_Green->FindRow<FTowerStatData>(*FString::FromInt(Level), TEXT(""));
		break;
	case ETowerColor::Blue:
		return TowerDataTable_Blue->FindRow<FTowerStatData>(*FString::FromInt(Level), TEXT(""));
		break;
	case ETowerColor::Black:
		return TowerDataTable_Black->FindRow<FTowerStatData>(*FString::FromInt(Level), TEXT(""));
		break;
	default:
		return nullptr;
		break;
	}
}