// Fill out your copyright notice in the Description page of Project Settings.

#include "GameContent/Item/ItemParent.h"
#include "Components/SphereComponent.h"
#include "Component/ACInventoryComponent.h"
#include "Framework/Game/C_Game.h"
#include "Kismet/GameplayStatics.h"

#include <Game/PS_Game.h>
#include <Game/GM_Game.h>
#include <Game/PC_Game.h>

#include <Protobuf/Handler/FClientPacketHandler.h>
#include <Protobuf/Handler/FGamePacketHandler.h>

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

void AItemParent::PickUpItem(AC_Game* inPlayer)
{
	UWorld* world = GetWorld();
	if (nullptr == world)
	{
		return;
	}

	ANetworkGameMode* gameMode = Cast<ANetworkGameMode>(world->GetAuthGameMode());
	if (nullptr == gameMode)
	{
		return;
	}

	ANetworkController* controller = gameMode->GetNetworkController();
	if (nullptr == controller)
	{
		return;
	}

	AC_Game* player = Cast<AC_Game>(controller->GetPawn());
	if (nullptr == player)
	{
		return;
	}

	if (player != inPlayer)
	{
		return;
	}

	
	//if (false == player->mInventoryComponent->TryAddItem(mItemObjectData))
	//{
	//	return;
	//}

	Protocol::C2S_InsertInventory insertInventoryPacket;
	insertInventoryPacket.set_timestamp(controller->GetServerTimeStamp());
	Protocol::SItem* item = insertInventoryPacket.mutable_item();
	item->set_object_id(mGameObjectId);
	item->set_item_code(mItemCode);

	Protocol::SVector* worldPosition = item->mutable_world_position();
	FVector location = GetActorLocation();
	worldPosition->set_x(location.X);
	worldPosition->set_y(location.Y);
	worldPosition->set_z(location.Z);

	Protocol::SVector2D* invenPositon = item->mutable_inven_position();
	invenPositon->set_x(mItemObjectData->position_x);
	invenPositon->set_y(mItemObjectData->position_y);

	item->set_rotation(mItemObjectData->rotation);

	SendBufferPtr sendBuffer = FGamePacketHandler::MakeSendBuffer(controller, insertInventoryPacket);
	controller->Send(sendBuffer);
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