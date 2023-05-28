// Fill out your copyright notice in the Description page of Project Settings.

#include "GameContent/Item/ItemParent.h"
#include "Components/SphereComponent.h"
#include "Component/ACInventoryComponent.h"
#include "Framework/Game/C_Game.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AItemParent::AItemParent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	mSkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	RootComponent = mSkeletalMeshComponent;

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

void AItemParent::PickUpItem()
{
	AActor* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (PlayerPawn != nullptr)
	{
		if (Cast<AC_Game>(PlayerPawn)->mInventoryComponent->TryAddItem(mItemObjectData))
		{
			Destroy();
		}
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