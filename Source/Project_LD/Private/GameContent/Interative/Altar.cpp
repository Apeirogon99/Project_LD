// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Interative/Altar.h"

#include "Components/SphereComponent.h"

#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

#include "Components/WidgetComponent.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

#include <Widget/Common/W_EnterDungeon.h>
#include <Handler/ClientHUD.h>

// Sets default values
AAltar::AAltar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = mSceneComponent;

	mStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mStaticMeshComponent->SetupAttachment(RootComponent);

	mParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	mParticleSystem->SetupAttachment(RootComponent);
	mParticleSystem->bAutoActivate = true;
	mParticleSystem->SetRelativeLocation(FVector(0.0f, 20.0f, 160.0f));

	mSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	mSphere->InitSphereRadius(300.0f);
	mSphere->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(TEXT("StaticMesh'/Game/Stylized_Graveyard/meshes/props/SM_wooden_altar.SM_wooden_altar'"));
	if (mesh.Succeeded())
	{
		mStaticMeshComponent->SetStaticMesh(mesh.Object);
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> particle(TEXT("ParticleSystem'/Game/Blueprint/Level/MainStage/P_Smoke_MainStage.P_Smoke_MainStage'"));
	if (particle.Succeeded())
	{
		mParticleSystem->SetTemplate(particle.Object);
	}

	Tags.Add(FName("Interative"));
}

// Called when the game starts or when spawned
void AAltar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAltar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAltar::Interactive(ANC_Game* inPlayer)
{
	if (false == mIsOverlap)
	{
		return;
	}

	ANetworkController* networkController = Cast<ANetworkController>(inPlayer->GetController());
	if (nullptr == networkController)
	{
		return;
	}

	AClientHUD* clientHUD = Cast<AClientHUD>(networkController->GetHUD());
	if (nullptr == clientHUD)
	{
		return;
	}

	UW_EnterDungeon* dungeon = nullptr;
	UUserWidget* outWidget = clientHUD->GetWidgetFromName(TEXT("EnterDungeon"));
	if (outWidget == nullptr)
	{
		return;
	}

	dungeon = Cast<UW_EnterDungeon>(outWidget);
	if (dungeon == nullptr)
	{
		return;

	}
	dungeon->SetTitle(TEXT("공동묘지 제단"));
	dungeon->SetMessage(TEXT("어두운 힘의 기운이 제단을 감싸고 있습니다"));
	dungeon->SetDungeon(1);

	clientHUD->ShowWidgetFromName(TEXT("EnterDungeon"));
}

