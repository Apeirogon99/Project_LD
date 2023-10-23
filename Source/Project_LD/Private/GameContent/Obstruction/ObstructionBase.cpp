// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Obstruction/ObstructionBase.h"
#include <Framework/Gameinstance/LDGameInstance.h>
#include "Components/BoxComponent.h"

AObstructionBase::AObstructionBase()
{
	PrimaryActorTick.bCanEverTick = false;

	mBlocking = CreateDefaultSubobject<UBoxComponent>(TEXT("Blocking"));
	mBlocking->InitBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	mBlocking->SetHiddenInGame(false);
	mBlocking->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	mBlocking->SetCollisionProfileName(FName("BlockAll"));

	RootComponent = mBlocking;

	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mMesh->SetupAttachment(RootComponent);
	mMesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	mMesh->SetCollisionProfileName(FName("BlockAll"));
}

void AObstructionBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AObstructionBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AObstructionBase::SetObstructioType(int32 inType)
{
	if (inType == 1)
	{
		return;
	}

	UWorld* world = GetWorld();
	if (nullptr == world)
	{
		return;
	}

	ULDGameInstance* instance = Cast<ULDGameInstance>(world->GetGameInstance());
	if (nullptr == instance)
	{
		return;
	}

	FObstructionData* data = instance->GetObstructionData(inType);
	if (nullptr == data)
	{
		return;
	}

	UStaticMesh* staticMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, *data->mPath));
	if (staticMesh && mMesh)
	{
		mMesh->SetStaticMesh(staticMesh);
	}
}

void AObstructionBase::SetBlockingExtent(FVector inExtent)
{
	if (mBlocking)
	{
		mBlocking->SetBoxExtent(inExtent);
	}
}

