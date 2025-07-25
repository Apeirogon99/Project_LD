// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Skill/Skill_Buff.h"
#include "Niagara/Public/NiagaraComponent.h"
#include "Niagara/Classes/NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include <Components/SphereComponent.h>
#include <Framework/Game/NC_Game.h>
#include "UObject/ConstructorHelpers.h"
#include <GS_Game.h>
#include <C_Game.h>
#include <NetworkGameMode.h>
#include <PC_Game.h>

// Sets default values
ASkill_Buff::ASkill_Buff()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	mPlayerInCheckCollision = CreateDefaultSubobject<USphereComponent>(TEXT("CheckCollision"));
	mPlayerInCheckCollision->SetupAttachment(RootComponent);
	mPlayerInCheckCollision->SetSphereRadius(430.f);
	mPlayerInCheckCollision->OnComponentBeginOverlap.AddUniqueDynamic(this, &ASkill_Buff::OnOverlapBegin);
	mPlayerInCheckCollision->OnComponentEndOverlap.AddUniqueDynamic(this, &ASkill_Buff::OnOverlapEnd);
	mPlayerInCheckCollision->SetGenerateOverlapEvents(false);

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> SUMMON_PARTICLE(TEXT("NiagaraSystem'/Game/GameContent/Animation/Male/Skill/Buff/NS_Buff_Summon.NS_Buff_Summon'"));
	if (SUMMON_PARTICLE.Succeeded())
	{
		mSummonParticle = SUMMON_PARTICLE.Object;
	}

	IsLocalParty = false;
}

void ASkill_Buff::AppearSkill(const int64 InRemoteID, const int64 InObjectID, const int32 InSkillID, const FVector InLocation, const FRotator InRotation, const float InDuration)
{
	Super::AppearSkill(InRemoteID,InObjectID,InSkillID,InLocation,InRotation,InDuration);

	if (mSummonParticle)
	{
		mRemoteID = InRemoteID;
		mObjectID = InObjectID;
		FVector Location = InLocation;
		Location.Z = Location.Z - 80.f;
		mSpawnedParticle = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), mSummonParticle, Location, FRotator(), FVector(5), true);
		mPlayerInCheckCollision->SetGenerateOverlapEvents(true);
	}
}

void ASkill_Buff::ReactionSkill(const int64 InRemoteID, const int64 InObjectID, const int32 InSkillID, const FVector InLocation, const FRotator InRotation, const float InDuration)
{
	Super::ReactionSkill(InRemoteID, InObjectID, InSkillID, InLocation, InRotation, InDuration);
}

// Called every frame
void ASkill_Buff::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (mSpawnedParticle)
	{
		FRotator Rot = mSpawnedParticle->GetRelativeRotation();
		Rot.Yaw = 0.f;
		mSpawnedParticle->SetRelativeRotation(Rot);
	}
}

// protected //
// Called when the game starts or when spawned
void ASkill_Buff::BeginPlay()
{
	Super::BeginPlay();
	/*
	UWorld* world = GetWorld();
	if (nullptr == world)
	{
		return;
	}

	ANetworkGameMode* gamemode = Cast<ANetworkGameMode>(world->GetAuthGameMode());
	if (nullptr == gamemode)
	{
		return;
	}
 
	APC_Game* localPlayerController = Cast<APC_Game>(gamemode->GetNetworkController());
	if (nullptr == localPlayerController)
	{
		return;
	}

	APS_Game* localPlayerState = localPlayerController->GetPlayerState<APS_Game>();
	if (nullptr == localPlayerState)
	{
		return;
	}

	TArray<APlayerState*> PartyPlayers;
	TArray<FPartyPlayerInfo> PartyPlayerInfos;
	UACPartyComponent* PartyComponent = localPlayerState->GetPartyComponent();
	if (nullptr == PartyComponent)
	{
		return;
	}

	PartyComponent->GetPartyPlayers(PartyPlayers, PartyPlayerInfos);
	for (auto partyplayer : PartyPlayers)
	{
		ANPS_Game* nonPlayerState = Cast<ANPS_Game>(partyplayer);
		if (nullptr == nonPlayerState)
		{
			return;
		}

		if (nonPlayerState->GetRemoteID() == mRemoteID)
		{
			IsLocalParty = true;
		}
	}
	*/
}

void ASkill_Buff::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (mSpawnedParticle)
	{
		mSpawnedParticle->DestroyComponent();
	}

	if (UNiagaraSystem* Niagara = LoadObject<UNiagaraSystem>(nullptr, TEXT("NiagaraSystem'/Game/GameContent/Animation/Male/Skill/Buff/NS_Buff_Disappear.NS_Buff_Disappear'")))
	{
		FVector Location = GetActorLocation();
		Location.Z = Location.Z - 90.f;
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Niagara, Location);
	}
}

void ASkill_Buff::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//if(IsLocalParty)

	if (Cast<AC_Game>(OtherActor) != nullptr)
	{
		if ((mRemoteID == 0) && (mObjectID == 0))
		{
			return;
		}

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

		AController* playercontroller = gameState->FindPlayerController(mRemoteID);
		if (nullptr == playercontroller)
		{
			return;
		}

		AActor* player = playercontroller->GetCharacter();
		if (nullptr == player)
		{
			return;
		}

		AC_Game* localPlayer = Cast<AC_Game>(player);
		if (nullptr == localPlayer)
		{
			return;
		}

		APS_Game* playerState = localPlayer->GetPlayerState<APS_Game>();
		if (nullptr == playerState)
		{
			return;
		}

		UACPartyComponent* party = playerState->GetPartyComponent();
		if (nullptr == party)
		{
			return;
		}

		TArray<APlayerState*>			outPartyPlayers;
		TArray<FPartyPlayerInfo>		outPartyPlayerInfos;

		party->GetPartyPlayers(outPartyPlayers, outPartyPlayerInfos);

		if (outPartyPlayers.Num() == 0)
		{
			Cast<AC_Game>(OtherActor)->ActiveBuffParticle();
		}
	}
}

void ASkill_Buff::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<AC_Game>(OtherActor) != nullptr)
	{
		if ((mRemoteID == 0) && (mObjectID == 0))
		{
			return;
		}

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

		AController* playercontroller = gameState->FindPlayerController(mRemoteID);
		if (nullptr == playercontroller)
		{
			return;
		}

		AActor* player = playercontroller->GetCharacter();
		if (nullptr == player)
		{
			return;
		}

		AC_Game* localPlayer = Cast<AC_Game>(player);
		if (nullptr == localPlayer)
		{
			return;
		}

		APS_Game* playerState = localPlayer->GetPlayerState<APS_Game>();
		if (nullptr == playerState)
		{
			return;
		}

		UACPartyComponent* party = playerState->GetPartyComponent();
		if (nullptr == party)
		{
			return;
		}

		TArray<APlayerState*>			outPartyPlayers;
		TArray<FPartyPlayerInfo>		outPartyPlayerInfos;

		party->GetPartyPlayers(outPartyPlayers, outPartyPlayerInfos);

		if (outPartyPlayers.Num() == 0)
		{
			Cast<AC_Game>(OtherActor)->DeActiveBuffParticle();
		}
	}
}
