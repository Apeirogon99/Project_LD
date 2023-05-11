// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework/Character/GameCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include <Component/ACInventoryComponent.h>
#include "GameContent/Item/ItemParent.h"

#include <Widget/Game/Inventory/UWInventory.h>
#include "Blueprint/UserWidget.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

//#include "Components/DecalComponent.h"

AGameCharacter::AGameCharacter()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> MainWidgetAsset(TEXT("WidgetBlueprint'/Game/TestFolder/TestCharacter/widget/BW_Inventory.BW_Inventory_C'"));
	if (MainWidgetAsset.Succeeded())
	{
		MainWidgetClass = MainWidgetAsset.Class;
	}

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false;

	GameCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	GameCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	GameCameraComponent->bUsePawnControlRotation = false;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("PlayerCharacter"));

/**Character Status Setting**/

	//Attack Range
	AttackRange = 200.0f;	AttackRadius = 50.0f;
	//Attack Info
	IsAttacking = false;
	//Health
	MaxHealth = 100.0f;	CurrentHealth = 100.0f;
	//Mana
	MaxMana = 100.0f;		CurrentMana = 100.0f;
	//Character Level
	CharacterLevel = 1;

	InventoryComponent = CreateDefaultSubobject<UACInventoryComponent>(TEXT("InventoryComponent"));

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

AGameCharacter::~AGameCharacter()
{

}

void AGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("ToggleInventory", IE_Pressed, this, &AGameCharacter::OpenInventory);
	PlayerInputComponent->BindAction("InteractItem", IE_Pressed, this, &AGameCharacter::InteractItem);
}

void AGameCharacter::OpenInventory()
{
	if (InventoryWidget->IsInViewport())
	{
		InventoryWidget->RemoveFromParent();
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (PlayerController != nullptr)
		{
			FInputModeGameOnly InputMode;
			PlayerController->SetInputMode(InputMode);
			PlayerController->bShowMouseCursor = false;
			Cast<UUWGridInventory>(InventoryWidget->GridInventory)->LineArr.Reset();
		}
	}
	else
	{
		InventoryWidget->AddToViewport();
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (PlayerController != nullptr)
		{
			FInputModeGameAndUI InputMode;
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			InputMode.SetHideCursorDuringCapture(false);
			PlayerController->SetInputMode(InputMode);
			PlayerController->bShowMouseCursor = true;
		}
	}
}

void AGameCharacter::InteractItem()
{
	TArray<AActor*> Result;
	GetOverlappingActors(Result, AItemParent::StaticClass());

	UE_LOG(LogTemp, Warning, TEXT("InteractItem"));
	for (auto& Actor : Result)
	{
		if (UKismetSystemLibrary::DoesImplementInterface(Actor, UInventoryInterface::StaticClass()))
		{
			UE_LOG(LogTemp, Warning, TEXT("InteractItem -> exist Interface"));
			AItemParent* Item = Cast<AItemParent>(Actor);
			if (Item != nullptr)
			{
				Item->PickUpItem();
			}
		}
	}
}

void AGameCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(MainWidgetClass))
	{
		InventoryWidget = Cast<UUWInventory>(CreateWidget(GetWorld(), MainWidgetClass));

		if (InventoryWidget)
		{
			InventoryWidget->TileSize = 50.0f;
			InventoryWidget->ACInventory = InventoryComponent;
		}
	}
}

void AGameCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	/*
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		FHitResult TraceHitResult;
		PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
		FVector CursorFV = TraceHitResult.ImpactNormal;
		FRotator CursorR = CursorFV.Rotation();
		CursorToWorld->SetWorldLocation(TraceHitResult.Location);
		CursorToWorld->SetWorldRotation(CursorR);
	}
	*/
}
