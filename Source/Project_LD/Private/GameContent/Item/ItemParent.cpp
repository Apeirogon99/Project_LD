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
	AActor::BeginPlay();

	/*
	//itemObjectData ���� Ȯ��
	if (ItemObjectData==nullptr)
	{
		UE_LOG(Logtemp, warning, TEXT("ItemObjectData is Not Init"));
	}
	*/

	/*
	//BeginOverlap �Լ� ����
	if (Sphere = GetOwner()->FindComponentByClass<USphereComponent>())
	{
		Sphere->OnComponentBeginOverlap.AddDynamic(this, &AItemParent::OnActorBeginOverlap);
	}
	*/
}

void AItemParent::OnActorBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//ĳ���Ϳ� �������� ���� ��� Pickup Widget�� ����
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
