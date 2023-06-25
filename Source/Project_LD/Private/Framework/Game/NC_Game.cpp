// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Game/NC_Game.h"
#include "Framework/Game/NPC_Game.h"
#include "Framework/Game/GS_Game.h"
#include "Framework/Game/PS_Game.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ANC_Game::ANC_Game()
{
	//PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("PlayerCharacter"));

	AIControllerClass = ANPC_Game::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

ANC_Game::~ANC_Game()
{
}

void ANC_Game::BeginPlay()
{
	Super::BeginPlay();
}

void ANC_Game::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ANC_Game::Destroyed()
{

	//Super::Destroyed();

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

	ANPC_Game* controller = Cast<ANPC_Game>(GetController());
	if (nullptr == controller)
	{
		return;
	}

	ANPS_Game* playerState = controller->GetPlayerState<ANPS_Game>();
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
