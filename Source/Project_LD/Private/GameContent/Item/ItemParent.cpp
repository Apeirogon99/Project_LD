// Fill out your copyright notice in the Description page of Project Settings.

#include "GameContent/Item/ItemParent.h"
#include "Components/SphereComponent.h"
#include "Component/ACInventoryComponent.h"
#include "Framework/Game/C_Game.h"
#include "Kismet/GameplayStatics.h"

#include <Game/PS_Game.h>

// Sets default values
AItemParent::AItemParent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	mSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = mSceneComponent;

	mSkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	mSkeletalMeshComponent->SetupAttachment(RootComponent);

	//Sphere Collision
	mSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	mSphere->InitSphereRadius(50.0f);
	mSphere->SetupAttachment(RootComponent);
	mSphere->SetCollisionProfileName(TEXT("OverlapAll"));

	mItemCode = -1;
	mGameObjectId = -1;

	mIcon = nullptr;
}

// Called when the game starts or when spawned
void AItemParent::BeginPlay()
{
	Super::BeginPlay();
}

void AItemParent::PickUpItem(AC_Game* Player)
{
	AC_Game* Character = Player;

	if (Character == nullptr)
	{
		return;
	}

	APS_Game* PlayerState = Character->GetPlayerState<APS_Game>();
	if (PlayerState == nullptr)
	{
		return;
	}

	if (PlayerState->TryAddItem(mItemObjectData))
	{
		Destroy();
	}
}

void AItemParent::Init(int32 Code, int32 GameObjectId)
{
	mItemCode = Code;
	mGameObjectId = GameObjectId;

	mItemObjectData = NewObject<UItemObjectData>();

	ULDGameInstance* Instance = Cast<ULDGameInstance>(GetWorld()->GetGameInstance());
	FItemData* ItemTable = Instance->GetItemData(mItemCode);

	mItemObjectData->ItemData = *ItemTable;
	ItemObjectDataInit();
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), mMouseCursorParticle, GetActorLocation(), FRotator::ZeroRotator, true);
}

void AItemParent::ItemObjectDataInit()
{
	//Mesh
	mSkeletalMeshComponent->SetSkeletalMesh(mItemObjectData->ItemData.mesh);
	mIcon = mItemObjectData->ItemData.icon;
}