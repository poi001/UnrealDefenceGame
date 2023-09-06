// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DGTileActor.generated.h"

UCLASS()
class UNREALDEFENCEGAME_API ADGTileActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADGTileActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Tile")
	bool IsSelecting;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Tile")
	bool IsOn;

	TWeakObjectPtr<class ADGTowerActor> DGTowerActor;

	UFUNCTION(BlueprintCallable)
	void SetMaterialBasic();
	UFUNCTION(BlueprintCallable)
	void SetMaterialSelect();

	void SpawnTowerActor();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tile", meta = (AllowProtectedAccess = true))
	class USceneComponent* RootScene;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tile", meta = (AllowProtectedAccess = true))
	class UStaticMeshComponent* Tile;
	UFUNCTION(BlueprintCallable)
	void OnClickedTile();

private:
	UPROPERTY()
	class ADGGameStateBase* DGGameStateBase;
	UPROPERTY()
	class ADGPlayerController* DGPlayerController;

	UPROPERTY()
	class UMaterial* TileBasicMaterial;
	UPROPERTY()
	class UMaterial* TileSelectMaterial;
};
