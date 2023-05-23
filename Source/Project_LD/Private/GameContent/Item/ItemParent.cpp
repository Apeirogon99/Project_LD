// Fill out your copyright notice in the Description page of Project Settings.

#include "GameContent/Item/ItemParent.h"

// Sets default values
AItemParent::AItemParent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//StaticMesh
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMeshComponent;

	//Sphere Collision
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Sphere->InitSphereRadius(50.0f);
	Sphere->SetupAttachment(RootComponent);
	Sphere->SetCollisionProfileName(TEXT("OverlapAll"));
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
		if (Cast<AGameCharacter>(PlayerPawn)->InventoryComponent->TryAddItem(ItemObjectData))
		{
			Destroy();
		}
	}
}