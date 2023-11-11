// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Enemy/E_DarkKnight.h"
#include "GameContent/Enemy/EnemyController.h"
#include "GameContent/Enemy/EnemyState.h"
#include <Framework/Game/GS_Game.h>
#include <GameContent/Enemy/DarkKnightAnimInstance.h>

#include "Niagara/Public/NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

#include <Network/NetworkUtils.h>

AE_DarkKnight::AE_DarkKnight()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	//static ConstructorHelpers::FObjectFinder<UMaterialInterface> materialInterface(TEXT("MaterialInstanceConstant'/Game/GameContent/Mat/HitMat/MI_DarkKnightHit.MI_DarkKnightHit'"));
	//if (materialInterface.Succeeded())
	//{
	//	mHitMaterialInstance = GetMesh()->CreateDynamicMaterialInstance(0, materialInterface.Object);
	//	mHitMaterialInstance->SetVectorParameterValue(FName("EmissiveColor"), FLinearColor::Transparent);
	//	mHitMaterialInstance->SetScalarParameterValue(FName("EmissiveMul"), 0.0f);
	//}
}

AE_DarkKnight::~AE_DarkKnight()
{
}

void AE_DarkKnight::PlayDarkKnightAnim(int32 Index)
{
	UDarkKnightAnimInstance* animInstance = Cast<UDarkKnightAnimInstance>(GetMesh()->GetAnimInstance());
	if (animInstance == nullptr)
	{
		return;
	}
	animInstance->PlayDarkKnightAnimMontage(Index);
}

void AE_DarkKnight::ActiveBerserk()
{
	if (UNiagaraSystem* Niagara = LoadObject<UNiagaraSystem>(nullptr, TEXT("NiagaraSystem'/Game/GameContent/Animation/Enemy/DarkKnight/Particle/NS_DarkKnight_Berserk.NS_DarkKnight_Berserk'")))
	{
		FVector Loc = GetActorLocation();
		Loc.Z = Loc.Z - 50.f;
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Niagara, Loc, FRotator(0.f,90.f,0.f), FVector(1), true);
	}
	if (UNiagaraSystem* Niagara = LoadObject<UNiagaraSystem>(nullptr, TEXT("NiagaraSystem'/Game/GameContent/Animation/Enemy/DarkKnight/Particle/NS_DarkFlame_1.NS_DarkFlame_1'")))
	{
		mBerserkNiagara = UNiagaraFunctionLibrary::SpawnSystemAttached(Niagara, GetMesh(), TEXT("None"), FVector(0.f, 0.f, 55.f), FRotator(0), EAttachLocation::SnapToTarget, false);
	}
}

void AE_DarkKnight::DarkKnightBladeParticleActive_Implementation()
{
}



void AE_DarkKnight::DarkKnightBladeParticleDeactive_Implementation()
{
}

void AE_DarkKnight::BeginPlay()
{
	Super::BeginPlay();
}

void AE_DarkKnight::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AE_DarkKnight::Destroyed()
{
	UWorld* world = GetWorld();
	if (nullptr == world)
	{
		return;
	}

	AGS_Game* gameState = Cast<AGS_Game>(world->GetGameState());
	if (nullptr == gameState)
	{
		return;
	}

	AEnemyController* controller = Cast<AEnemyController>(GetController());
	if (nullptr == controller)
	{
		return;
	}

	AEnemyState* playerState = controller->GetPlayerState<AEnemyState>();
	if (nullptr == playerState)
	{
		return;
	}

	if (mBerserkNiagara)
	{
		mBerserkNiagara->Deactivate();
		mBerserkNiagara->DestroyComponent();
	}

	HealthBarDeactive();

	controller->UnPossess();

	gameState->RemovePlayerState(playerState);

	playerState->Destroy();

	world->DestroyActor(playerState);

	world->DestroyActor(controller);
}

void AE_DarkKnight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
