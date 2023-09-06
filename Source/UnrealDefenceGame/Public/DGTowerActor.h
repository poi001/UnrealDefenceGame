// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UnrealDefenceGame.h"
#include "GameFramework/Actor.h"
#include "DGTowerActor.generated.h"

UCLASS()
class UNREALDEFENCEGAME_API ADGTowerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADGTowerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tower", meta = (AllowProtectedAccess = true))
	class USceneComponent* RootScene;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tower", meta = (AllowProtectedAccess = true))
	class UStaticMeshComponent* Tower;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TowerStatComponent")
	class UDGTowerActorComponent* TowerStatComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "TowerStatComponent")
	int32 Level;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "TowerStatComponent")
	ETowerColor Color;


	void InitializeTower(int32 TowerLevel, ETowerColor TowerType);

private:
	UPROPERTY()
	class UStaticMesh* TowerMesh;
	UPROPERTY()
	class UMaterialInstance* TowerMaterial;
	UPROPERTY()
	class ADGEnemyCharacter* DetectedEnemyCharacter;
	UPROPERTY()
	TSubclassOf<class ADGProjectile> DGProjectile;

	bool bIsDetected = false;
	float TickBasket = 0.0f;
	
	FSoftObjectPath TowerMeshToLoad = FSoftObjectPath(nullptr);
	FSoftObjectPath TowerMaterialToLoad = FSoftObjectPath(nullptr);
	TSharedPtr<struct FStreamableHandle> MeshStreamingHandle;
	TSharedPtr<struct FStreamableHandle> MaterialStreamingHandle;

	void DetectEnemy();
	void UnDetectEnemy();

	void OnMeshLoadCompleted();
	void OnMaterialLoadCompleted();

	void Shot();

	void DetectDrawDebug(FVector TargetLocation);
};
