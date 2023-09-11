// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Enemy/E_Lich.h"
#include "GameContent/Enemy/EnemyController.h"
#include "GameContent/Enemy/EnemyState.h"
#include <GameContent/Enemy/LichAnimInstance.h>
#include <Framework/Game/GS_Game.h>
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"

#include <Network/NetworkUtils.h>

AE_Lich::AE_Lich()
{
	mRightMultiCastParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("RightMultiCastParticle"));
	mLeftMultiCastParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("LeftMultiCastParticle"));
	mRightMultiCastParticle->SetupAttachment(RootComponent);
	mLeftMultiCastParticle->SetupAttachment(RootComponent);

	mLichCheckCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("CheckCollider"));
	mLichCheckCollider->SetupAttachment(GetMesh());
	mLichCheckCollider->SetCollisionProfileName(TEXT("NoCollision"));
	mLichCheckCollider->SetRelativeLocation(FVector(0.f, 0.f, 130.f));
	mLichCheckCollider->SetBoxExtent(FVector(70.f, 60.f, 90.f));
	mLichCheckCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	mLichCheckCollider->OnComponentBeginOverlap.AddDynamic(this, &AE_Lich::OnOverlapBegin);
}

AE_Lich::~AE_Lich()
{
}

void AE_Lich::PlayLichAnim(int32 Index)
{
	ULichAnimInstance* animInstance = Cast<ULichAnimInstance>(GetMesh()->GetAnimInstance());
	if (animInstance == nullptr)
	{
		return;
	}
	animInstance->PlayLichAnimMontage(Index);
}

void AE_Lich::ActiveMultiCastParticle()
{
	if (mRightMultiCastParticle && mLeftMultiCastParticle)
	{
		mRightMultiCastParticle->Activate();
		mLeftMultiCastParticle->Activate();
	}
}

void AE_Lich::OnDisappear_Implementation()
{
}

void AE_Lich::BeginPlay()
{
	Super::BeginPlay();
}

void AE_Lich::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AE_Lich::Destroyed()
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

void AE_Lich::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AC_Game>(OtherActor) != nullptr)
	{
		AC_Game* localplayer = Cast<AC_Game>(OtherActor);
		localplayer->PlayerLoseEyesight();
	}
}

void AE_Lich::OnAppear_Implementation()
{
}

void AE_Lich::Tick(float DeltaTime)
{
}
