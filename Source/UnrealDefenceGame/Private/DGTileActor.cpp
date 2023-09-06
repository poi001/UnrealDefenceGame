// Fill out your copyright notice in the Description page of Project Settings.


#include "DGTileActor.h"
#include "DGPlayerController.h"
#include "DGGameStateBase.h"
#include "DGTowerActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADGTileActor::ADGTileActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("SCENE"));
	Tile = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TILE"));
	RootComponent = RootScene;
	Tile->SetupAttachment(RootScene);

	ConstructorHelpers::FObjectFinder<UMaterial>TILESELECTMATERIAL(TEXT("/Game/Actor/etc/TileMaterial/MT_Select.MT_Select"));
	ConstructorHelpers::FObjectFinder<UMaterial>TILEBASICMATERIAL(TEXT("/Game/Actor/etc/TileMaterial/MT_Basic.MT_Basic"));
	if (TILESELECTMATERIAL.Succeeded())TileSelectMaterial = TILESELECTMATERIAL.Object;
	if (TILEBASICMATERIAL.Succeeded())TileBasicMaterial = TILEBASICMATERIAL.Object;

	IsSelecting = false;
	IsOn = false;
}

// Called when the game starts or when spawned
void ADGTileActor::BeginPlay()
{
	Super::BeginPlay();
	
	DGGameStateBase = Cast<ADGGameStateBase>(GetWorld()->GetGameState());
	DGPlayerController = Cast<ADGPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

// Called every frame
void ADGTileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADGTileActor::OnClickedTile()
{
	DGPlayerController->OpenTowerWidget(this);
}
void ADGTileActor::SetMaterialBasic()
{
	Tile->SetMaterial(0, TileBasicMaterial);
}
void ADGTileActor::SetMaterialSelect()
{
	Tile->SetMaterial(0, TileSelectMaterial);
}

void ADGTileActor::SpawnTowerActor()
{
	if (!DGTowerActor.IsValid())
	{
		DGTowerActor = GetWorld()->SpawnActor<ADGTowerActor>(ADGTowerActor::StaticClass(), GetActorTransform());
	}
}
