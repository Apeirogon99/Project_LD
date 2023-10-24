// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Enemy/E_ArcherSkeleton.h"
#include "GameContent/Enemy/EnemyController.h"
#include "GameContent/Enemy/EnemyState.h"
#include <Framework/Game/GS_Game.h>

#include <Network/NetworkUtils.h>

AE_ArcherSkeleton::AE_ArcherSkeleton()
{
	//static ConstructorHelpers::FObjectFinder<UMaterialInterface> materialInterface(TEXT("MaterialInstanceConstant'/Game/GameContent/Mat/HitMat/MI_SkeletonHit.MI_SkeletonHit'"));
	//if (materialInterface.Succeeded())
	//{
	//	mHitMaterialInstance = GetMesh()->CreateDynamicMaterialInstance(0, materialInterface.Object);
	//	mHitMaterialInstance->SetVectorParameterValue(FName("EmissiveColor"), FLinearColor::Transparent);
	//	mHitMaterialInstance->SetScalarParameterValue(FName("EmissiveMul"), 0.0f);
	//}
}

AE_ArcherSkeleton::~AE_ArcherSkeleton()
{
}

void AE_ArcherSkeleton::BeginPlay()
{
	Super::BeginPlay();
}

void AE_ArcherSkeleton::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AE_ArcherSkeleton::Destroyed()
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

	controller->UnPossess();

	gameState->RemovePlayerState(playerState);

	playerState->Destroy();

	world->DestroyActor(playerState);

	world->DestroyActor(controller);
}

void AE_ArcherSkeleton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}