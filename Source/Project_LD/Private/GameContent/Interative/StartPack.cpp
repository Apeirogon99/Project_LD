// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Interative/StartPack.h"
#include "Components/SphereComponent.h"

#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

#include "Components/WidgetComponent.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

#include <Widget/Common/W_Reconfirm.h>
#include <Handler/ClientHUD.h>
#include <Widget/WidgetUtils.h>

// Sets default values
AStartPack::AStartPack()
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

	static ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(TEXT("StaticMesh'/Game/Stylized_Graveyard/meshes/props/SM_wood_box_01.SM_wood_box_01'"));
	if (mesh.Succeeded())
	{
		mStaticMeshComponent->SetStaticMesh(mesh.Object);
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> particle(TEXT("ParticleSystem'/Game/Luos8Elements/Particles/Light/Par_4E_LightOrb_01.Par_4E_LightOrb_01'"));
	if (particle.Succeeded())
	{
		mParticleSystem->SetTemplate(particle.Object);
	}

	Tags.Add(FName("Interative"));

}

// Called when the game starts or when spawned
void AStartPack::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStartPack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStartPack::Interactive(ANC_Game* inPlayer)
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

	FConfirmButtonDelegate confirm;
	confirm.BindLambda([=]()
		{
			APlayerController* owningController = Cast<APlayerController>(inPlayer->GetController());
			ANetworkController* networkController = Cast<ANetworkController>(owningController);
			if (nullptr == networkController)
			{
				return;
			}

			clientHUD->ShowWidgetFromName(TEXT("LoadingServer"));

			Protocol::C2S_StartPack packet;

			SendBufferPtr sendBuffer = FGamePacketHandler::MakeSendBuffer(nullptr, packet);
			networkController->Send(sendBuffer);

			clientHUD->CleanWidgetFromName(TEXT("Reconfirm"));
		});

	FCancleButtonDelegate cancle;
	cancle.BindLambda([=]()
		{
			clientHUD->CleanWidgetFromName(TEXT("Reconfirm"));
		});

	UWidgetUtils::SetReconfirm(clientHUD, TEXT("스타트팩"), TEXT("기본적인 아이템들이 들어있습니다."), TEXT("받기"), TEXT("취소"), confirm, cancle);

}

