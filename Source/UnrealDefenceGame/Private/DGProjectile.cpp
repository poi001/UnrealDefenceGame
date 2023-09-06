// Fill out your copyright notice in the Description page of Project Settings.


#include "DGProjectile.h"
#include "DGEnemyCharacter.h"
#include "DGEnemyActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ADGProjectile::ADGProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("SCENE"));
	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PARTICLE"));

	RootComponent = RootScene;
	ParticleSystemComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ADGProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
/*void ADGProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}*/

void ADGProjectile::CollideProjectile(float Radius, FVector HitLocal, float Damage)
{
	float AdjustRadius = 1.0f;
	if (Radius >= 32.0f) AdjustRadius = Radius / 32.0f;
	ParticleSystemComponent->SetRelativeScale3D(FVector(AdjustRadius, AdjustRadius, AdjustRadius));

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	TArray<AActor*> IgnoreActors;
	TArray<AActor*> OutActors;

	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
	IgnoreActors.Add(this);

	bool IsOverlapped = UKismetSystemLibrary::SphereOverlapActors(GetWorld(), HitLocal, Radius, ObjectTypes,
		nullptr, IgnoreActors, OutActors);
	if (IsOverlapped)
	{
		for (int i = 0; i < OutActors.Num(); i++)
		{
			auto Enemy = Cast<ADGEnemyCharacter>(OutActors[i]);
			if (Enemy)
			{
				UE_LOG(LogTemp, Warning, TEXT("Enemy took Damage : %f"), Damage);
				Enemy->GetEnemyStat()->SetDamage(Damage);
			}
		}
	}
}