// Fill out your copyright notice in the Description page of Project Settings.

#include "GameContent/Item/ItemParent.h"
#include "Components/SphereComponent.h"
#include "Component/ACInventoryComponent.h"
#include "Components/WidgetComponent.h"
#include "Framework/Game/C_Game.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include <Widget/Game/Item/W_ItemName.h>
#include "Camera/CameraComponent.h"

#include <Game/PS_Game.h>
#include <Game/GM_Game.h>
#include <Game/PC_Game.h>

#include <UObject/ConstructorHelpers.h>

#include <Protobuf/Handler/FClientPacketHandler.h>
#include <Protobuf/Handler/FGamePacketHandler.h>

// Sets default values
AItemParent::AItemParent()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = mSceneComponent;

	mSkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	mSkeletalMeshComponent->SetupAttachment(RootComponent);

	//Sphere Collision
	mSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	mSphere->InitSphereRadius(20.0f);
	mSphere->SetupAttachment(RootComponent);
	mSphere->SetCollisionProfileName(TEXT("ItemCollision"));

	mIcon = nullptr;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BagMesh(TEXT("SkeletalMesh'/Game/Infinity_Blade_Assets/Meshes/SM_TreasureBags02.SM_TreasureBags02_SM_TreasureBags02'"));
	if (BagMesh.Succeeded())
	{
		mSkeletalMeshComponent->SetSkeletalMesh(BagMesh.Object);
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystemNormal(TEXT("ParticleSystem'/Game/GameContent/Particle/Item/P_Status_ItemHighlight_Normal.P_Status_ItemHighlight_Normal'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystemRare(TEXT("ParticleSystem'/Game/GameContent/Particle/Item/P_Status_ItemHighlight_Rare.P_Status_ItemHighlight_Rare'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystemEpic(TEXT("ParticleSystem'/Game/GameContent/Particle/Item/P_Status_ItemHighlight_Epic.P_Status_ItemHighlight_Epic'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystemUnique(TEXT("ParticleSystem'/Game/GameContent/Particle/Item/P_Status_ItemHighlight_Unique.P_Status_ItemHighlight_Unique'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystemLeagendary(TEXT("ParticleSystem'/Game/GameContent/Particle/Item/P_Status_ItemHighlight_Leagendary.P_Status_ItemHighlight_Leagendary'"));
	if (ParticleSystemNormal.Succeeded())
	{
		mPickUpParticle.Add(ParticleSystemNormal.Object);
	}
	if (ParticleSystemRare.Succeeded())
	{
		mPickUpParticle.Add(ParticleSystemRare.Object);
	}
	if (ParticleSystemEpic.Succeeded())
	{
		mPickUpParticle.Add(ParticleSystemEpic.Object);
	}
	if (ParticleSystemUnique.Succeeded())
	{
		mPickUpParticle.Add(ParticleSystemUnique.Object);
	}
	if (ParticleSystemLeagendary.Succeeded())
	{
		mPickUpParticle.Add(ParticleSystemLeagendary.Object);
	}

	mItemSpawnParticleComponent = nullptr;

	TSubclassOf<UW_ItemName> NameWidgetAsset = StaticLoadClass(UW_ItemName::StaticClass(), NULL, TEXT("WidgetBlueprint'/Game/Blueprint/Widget/Game/Item/BW_ItemName.BW_ItemName_C'"));
	if (NameWidgetAsset)
	{
		mItemNameClass = NameWidgetAsset;
	}

	mItemNameWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("NameWidget"));
	mItemNameWidgetComponent->SetupAttachment(RootComponent);
	mItemNameWidgetComponent->SetWidgetClass(mItemNameClass);
	mItemNameWidgetComponent->SetCollisionProfileName(TEXT("NoCollision"));
	mItemNameWidgetComponent->SetRelativeLocationAndRotation(FVector(0.f,0.f,60.f),FRotator(30.f,-180.f,0.f));
	
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystemGain(TEXT("ParticleSystem'/Game/GameContent/Particle/Item/P_PickUp.P_PickUp'"));
	if (ParticleSystemGain.Succeeded())
	{
		mItemGainParticle = ParticleSystemGain.Object;
	}

	mPlayer = nullptr;

	Tags.Add(FName("Item"));
}

// Called when the game starts or when spawned
void AItemParent::BeginPlay()
{
	Super::BeginPlay();
}

void AItemParent::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	/*
	if (mPlayer)
	{
		mItemNameWidgetComponent->SetWorldRotation((mPlayer->GetCameraComponent()->GetComponentLocation() - mItemNameWidgetComponent->GetComponentLocation()).Rotation());
	}
	else
	{
		FindPlayer();
	}
	*/
}

void AItemParent::Destroyed()
{
	Super::Destroyed();

	//particle ¼ÒÈ¯
	if (mItemSpawnParticleComponent)
	{
		mItemSpawnParticleComponent->DeactivateSystem();
		mItemSpawnParticleComponent->DestroyComponent();
		mItemSpawnParticleComponent = nullptr;
	}

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), mItemGainParticle, GetActorLocation(), FRotator::ZeroRotator, true);

	mItemNameWidgetComponent->DestroyComponent();
}

void AItemParent::Interactive(AC_Game* inPlayer)
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

	if (false == gameMode->CompareNetworkController(inPlayer->GetController()))
	{
		return;
	}

	APS_Game* playerstate = controller->GetPlayerState<APS_Game>();
	if (nullptr == playerstate)
	{
		return;
	}

	if (false == playerstate->mInventoryComponent->TryAddItem(mItemObjectData))
	{
		return;
	}

	playerstate->mInventoryComponent->SetInventoryPacket(mItemObjectData, EInventoryType::Insert);
}

void AItemParent::Init(int32 Code, int32 GameObjectId)
{

	mItemObjectData = NewObject<UItemObjectData>();

	mItemObjectData->mItemCode = Code;
	mItemObjectData->ObjectID = GameObjectId;

	//Data Table
	ULDGameInstance* Instance = Cast<ULDGameInstance>(GetWorld()->GetGameInstance());
	FItemData* ItemTable = Instance->GetItemData(mItemObjectData->mItemCode);
	mItemObjectData->ItemData = *ItemTable;
	ItemObjectDataInit(ItemTable->category_id);

	//Widget
	if (mItemNameWidgetComponent)
	{
		UUserWidget* namewidget = mItemNameWidgetComponent->GetWidget();
		if (namewidget)
		{
			UW_ItemName* itemnamewidget = Cast<UW_ItemName>(namewidget);
			if (itemnamewidget)
			{
				itemnamewidget->SetNameText(ItemTable->name);
				itemnamewidget->SetDesiredSizeInViewport(FVector2D(1000.f, 1000.f));
			}
		}
	}
		
	//Particle
	mItemSpawnParticle = mPickUpParticle[ItemTable->tier_id - 1];
	if (mItemSpawnParticle)
	{
		mItemSpawnParticleComponent = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), mItemSpawnParticle, GetActorLocation(), FRotator::ZeroRotator, true);
	}
}

void AItemParent::FindPlayer()
{
	/*
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

	mPlayer = player;
	*/
}

void AItemParent::ItemObjectDataInit(int32 Categoryid)
{
	//Mesh
	if (Categoryid > 7)
	{
		mSkeletalMeshComponent->SetSkeletalMesh(mItemObjectData->ItemData.mesh);
	}
	mIcon = mItemObjectData->ItemData.icon;
}