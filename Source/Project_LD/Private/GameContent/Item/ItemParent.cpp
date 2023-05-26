// Fill out your copyright notice in the Description page of Project Settings.

#include "GameContent/Item/ItemParent.h"

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

	ItemId = 1;

	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableObeject(TEXT("DataTable'/Game/TestFolder/TestDataTable.TestDataTable'"));
	if (DataTableObeject.Succeeded())
	{
		DataTable = DataTableObeject.Object;
	}

	Icon = nullptr;
}

AItemParent::AItemParent(int32 id)
{
	PrimaryActorTick.bCanEverTick = false;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	RootComponent = SkeletalMeshComponent;

	//Sphere Collision
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Sphere->InitSphereRadius(50.0f);
	Sphere->SetupAttachment(RootComponent);
	Sphere->SetCollisionProfileName(TEXT("OverlapAll"));

	ItemId = id;

	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableObeject(TEXT("DataTable'/Game/TestFolder/TestDataTable.TestDataTable'"));
	if (DataTableObeject.Succeeded())
	{
		DataTable = DataTableObeject.Object;
	}

	Icon = nullptr;
}

// Called when the game starts or when spawned
void AItemParent::BeginPlay()
{
	Super::BeginPlay();

	ItemObjectData = NewObject<UItemObjectData>();

	FItemData* ItemTable = DataTable->FindRow<FItemData>(FName(*(FString::FormatAsNumber(ItemId))), FString(""));

	ItemObjectData->ItemData = *ItemTable;
	ItemObjectDataInit();
}

void AItemParent::PickUpItem()
{
	AActor* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (PlayerPawn != nullptr)
	{
		if (Cast<AGameCharacter>(PlayerPawn)->InventoryComponent->TryAddItem(ItemObjectData))
		{
			Destroy();
		}
	}
}

void AItemParent::ItemObjectDataInit()
{
	//Mesh
	SkeletalMeshComponent->SetSkeletalMesh(ItemObjectData->ItemData.mesh);
	Icon = ItemObjectData->ItemData.icon;
}
