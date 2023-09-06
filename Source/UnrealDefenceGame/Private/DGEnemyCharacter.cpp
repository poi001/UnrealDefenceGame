// Fill out your copyright notice in the Description page of Project Settings.


#include "DGEnemyCharacter.h"
#include "DGEnemyActorComponent.h"
#include "DGEnemyAnimInstance.h"
#include "DGEnemyHPBarWidget.h"
#include "DGGameStateBase.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ADGEnemyCharacter::ADGEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DGEnemyStat = CreateDefaultSubobject<UDGEnemyActorComponent>(TEXT("ENEMYSTATCOMPONENT"));
	DGEnemyHPWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("ENEMYHPWIDGET"));

	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -88.0f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	static ConstructorHelpers::FClassFinder<UDGEnemyHPBarWidget>ENEMYHPBAR(TEXT("/Game/Widget/BP_EnemyHPBar.BP_EnemyHPBar_C"));
	if (ENEMYHPBAR.Succeeded())
	{
		DGEnemyHPWidget->SetWidgetClass(ENEMYHPBAR.Class);
		DGEnemyHPWidget->SetDrawSize(FVector2D(100.0f, 33.0f));
	}
	DGEnemyHPWidget->SetupAttachment(GetMesh());
	//DGEnemyHPWidget->SetRelativeLocation(FVector(90.0f, 0.0f, 0.0f));//agonize
	DGEnemyHPWidget->SetWidgetSpace(EWidgetSpace::Screen);
}

// Called when the game starts or when spawned
void ADGEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetEnemyStat(DGGameStateBase->CurrentLevel);

	DGEnemyStat->OnHPIsZero.AddLambda([this]()->void {
		DGEnemyAnim->IsDead = true;
		DGGameStateBase->PlayerGold += DGEnemyStat->GetGold();
		DGGameStateBase->OnChangePlayerStatDelegate.Broadcast();
		Destroy();
		}
	);
}

// Called every frame
void ADGEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//DGEnemyStat->SetDamage(1.0f);
}

void ADGEnemyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	DGEnemyAnim = Cast<UDGEnemyAnimInstance>(GetMesh()->GetAnimInstance());
	DGGameStateBase = Cast<ADGGameStateBase>(GetWorld()->GetGameState());
}

float ADGEnemyCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator,
	AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	UE_LOG(LogTemp, Warning, TEXT("Enemy : %s took Damage : %f"), FinalDamage);
	DGEnemyStat->SetDamage(FinalDamage);

	return FinalDamage;
}

void ADGEnemyCharacter::SetEnemyStat(int32 Level)
{
	DGEnemyStat->SetNewNum(Level);
	GetCharacterMovement()->MaxWalkSpeed = DGEnemyStat->GetSpeed();

	auto EnemyHPBarWidget = Cast<UDGEnemyHPBarWidget>(DGEnemyHPWidget->GetUserWidgetObject());
	if (nullptr != EnemyHPBarWidget)
	{
		EnemyHPBarWidget->BindEnemyStat(DGEnemyStat);
	}
}

void ADGEnemyCharacter::OnOverlappedGoalActor()
{
	DGGameStateBase->PlayerLife = FMath::Clamp<int32>(DGGameStateBase->PlayerLife - DGEnemyStat->GetAttack(), 0, 20);
	DGGameStateBase->OnChangePlayerStatDelegate.Broadcast();
	if (DGGameStateBase->PlayerLife <= 0)
	{
		DGGameStateBase->OnPlayerLifeIsZero.Broadcast();
	}
	Destroy();
}