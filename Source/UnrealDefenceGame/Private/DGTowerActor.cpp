// Fill out your copyright notice in the Description page of Project Settings.


#include "DGTowerActor.h"
#include "DGTowerActorComponent.h"
#include "DGGameInstance.h"
#include "DGSetting.h"
#include "DGProjectile.h"
#include "DGEnemyCharacter.h"
#include "DrawDebugHelpers.h"

#define TOWERMAXLEVEL 3
#define NUMOFTOWERTYPE 5

// Sets default values
ADGTowerActor::ADGTowerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FClassFinder<ADGProjectile>PROJECTILE(TEXT("/Game/Actor/Projectile/BP_Projectile.BP_Projectile_C"));
	if (PROJECTILE.Succeeded()) DGProjectile = PROJECTILE.Class;

	TowerStatComponent = CreateDefaultSubobject<UDGTowerActorComponent>(TEXT("TOWERSTATCOMPONENT"));
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("SCENE"));
	Tower = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TOWER"));
	RootComponent = RootScene;
	Tower->SetupAttachment(RootScene);

	Tower->SetCollisionProfileName(FName("NoCollision"));

	DetectedEnemyCharacter = nullptr;

	Level = 1;
	Color = ETowerColor::Red;
}

// Called when the game starts or when spawned
void ADGTowerActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ADGTowerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsDetected)
	{
		UnDetectEnemy();
		if (TowerStatComponent->GetAS() <= TickBasket)
		{
			TickBasket = 0.0f;
			Shot();
		}
		else
		{
			TickBasket += DeltaTime;
		}
	}
	else
	{
		DetectEnemy();
		TickBasket = 0.0f;
	}
}

void ADGTowerActor::InitializeTower(int32 TowerLevel, ETowerColor TowerType)
{
	Level = TowerLevel;
	Color = TowerType;

	auto DefaultSetting = GetDefault<UDGSetting>();
	int32 AdjustTowerLevel = FMath::Clamp<int32>(TowerLevel - 1, 0, TOWERMAXLEVEL - 1);
	TowerMeshToLoad = DefaultSetting->TowerMesh[AdjustTowerLevel];
	int32 AdjustTowerType = FMath::Clamp<int32>(static_cast<int32>(TowerType), 0, NUMOFTOWERTYPE - 1);
	TowerMaterialToLoad = DefaultSetting->TowerMaterialInstance[AdjustTowerType];
	auto DGGameInstance = Cast<UDGGameInstance>(GetGameInstance());
	MeshStreamingHandle = DGGameInstance->StreamableManager.RequestAsyncLoad(TowerMeshToLoad,
		FStreamableDelegate::CreateUObject(this, &ADGTowerActor::OnMeshLoadCompleted));
	MaterialStreamingHandle = DGGameInstance->StreamableManager.RequestAsyncLoad(TowerMaterialToLoad,
		FStreamableDelegate::CreateUObject(this, &ADGTowerActor::OnMaterialLoadCompleted));

	TowerStatComponent->SetNewLevelAndType(TowerLevel, TowerType);
}

void ADGTowerActor::OnMeshLoadCompleted()
{
	UStaticMesh* MeshLoaded = Cast<UStaticMesh>(MeshStreamingHandle->GetLoadedAsset());
	MeshStreamingHandle.Reset();
	Tower->SetStaticMesh(MeshLoaded);
}
void ADGTowerActor::OnMaterialLoadCompleted()
{
	UMaterialInstance* MaterialLoaded = Cast<UMaterialInstance>(MaterialStreamingHandle->GetLoadedAsset());
	MaterialStreamingHandle.Reset();
	Tower->SetMaterial(0, MaterialLoaded);
}

void ADGTowerActor::DetectEnemy()
{
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, GetOwner());
	bool bResult = GetWorld()->OverlapMultiByChannel(
		OverlapResults,
		GetActorLocation(),
		FQuat::Identity,
		ECollisionChannel::ECC_Pawn,
		FCollisionShape::MakeSphere(512.0f),
		CollisionQueryParam
	);
	if (bResult)
	{
		for (auto const& OverlapResult : OverlapResults)
		{
			DetectedEnemyCharacter = Cast<ADGEnemyCharacter>(OverlapResult.GetActor());
			if (DetectedEnemyCharacter)
			{
				bIsDetected = true;
				return;
			}
		}
	}
}
void ADGTowerActor::UnDetectEnemy()
{
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, GetOwner());
	bool bResult = GetWorld()->OverlapMultiByChannel(
		OverlapResults,
		GetActorLocation(),
		FQuat::Identity,
		ECollisionChannel::ECC_Pawn,
		FCollisionShape::MakeSphere(512.0f),
		CollisionQueryParam
	);
	if (bResult)
	{
		for (auto const& OverlapResult : OverlapResults)
		{
			auto DetectedEnemy = Cast<ADGEnemyCharacter>(OverlapResult.GetActor());
			if (DetectedEnemyCharacter == DetectedEnemy) return;
		}
	}
	bIsDetected = false;
}

void ADGTowerActor::Shot()
{
	if (DetectedEnemyCharacter != nullptr)
	{
		GetWorld()->SpawnActor<ADGProjectile>(DGProjectile, DetectedEnemyCharacter->GetTransform())->
			CollideProjectile(TowerStatComponent->GetAR(), DetectedEnemyCharacter->GetActorLocation(), TowerStatComponent->GetAD());
	}
}

void ADGTowerActor::DetectDrawDebug(FVector TargetLocation)
{
	if (bIsDetected)
	{
		DrawDebugSphere(GetWorld(), GetActorLocation(), 512.0f, 16, FColor::Green, false, 0.2f);
		DrawDebugPoint(GetWorld(), TargetLocation, 10.0f, FColor::Blue, false, 0.2f);
		DrawDebugLine(GetWorld(), GetActorLocation(), TargetLocation, FColor::Green, false, 0.2f);
	}
	else
	{
		DrawDebugSphere(GetWorld(), GetActorLocation(), 512.0f, 16, FColor::Red, false, 0.2f);
	}
}