// Fill out your copyright notice in the Description page of Project Settings.

#include "GameContent/Item/ItemParent.h"
#include "Components/SphereComponent.h"
#include "Component/ACInventoryComponent.h">"
#include "Framework/Game/C_Game.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AItemParent::AItemParent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	RootComponent = SkeletalMeshComponent;

	//Sphere Collision
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Sphere->InitSphereRadius(50.0f);
	Sphere->SetupAttachment(RootComponent);
	Sphere->SetCollisionProfileName(TEXT("OverlapAll"));

	mItemCode = -1;
	mGameObjectId = -1;

	Icon = nullptr;
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
		if (Cast<AC_Game>(PlayerPawn)->InventoryComponent->TryAddItem(ItemObjectData))
		{
			Destroy();
		}
	}
}

void AItemParent::Init(int32 Code, int32 GameObjectId)
{
	mItemCode = Code;
	mGameObjectId = GameObjectId;

	ItemObjectData = NewObject<UItemObjectData>();

	ULDGameInstance* Instance = Cast<ULDGameInstance>(GetWorld()->GetGameInstance());
	FItemData* ItemTable = Instance->GetItemData(mItemCode);

	ItemObjectData->ItemData = *ItemTable;
	ItemObjectDataInit();
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), mMouseCursorParticle, GetActorLocation(), FRotator::ZeroRotator, true);
}

void AItemParent::ItemObjectDataInit()
{
	//Mesh
	SkeletalMeshComponent->SetSkeletalMesh(ItemObjectData->ItemData.mesh);
	Icon = ItemObjectData->ItemData.icon;
}