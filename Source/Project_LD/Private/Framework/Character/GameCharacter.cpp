// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework/Character/GameCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include <Widget/Game/Inventory/UWInventory.h>
#include <Component/ACInventoryComponent.h>

//#include "Components/DecalComponent.h"

AGameCharacter::AGameCharacter()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> MainWidgetAsset(TEXT("WidgetBlueprint'/Game/TestFolder/TestCharacter/widget/BP_UWInventory.BP_UWInventory_C'"));
	if (MainWidgetAsset.Succeeded())
	{
		MainWidgetClass = MainWidgetAsset.Class;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Fail Character"));
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
}

void AGameCharacter::OpenInventory()
{
	UE_LOG(LogTemp, Warning, TEXT("OpenInven"));

	UE_LOG(LogTemp, Warning, TEXT("IsInViewport %d"),InventoryWidget->IsInViewport());

	if (InventoryWidget->IsInViewport())
	{
		UE_LOG(LogTemp, Warning, TEXT("InventoryWidget->IsInViewport() is ture"));
		InventoryWidget->RemoveFromParent();
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (PlayerController != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("PlayerContorller is exist, GameOnly"));
			FInputModeGameOnly InputMode;
			PlayerController->SetInputMode(InputMode);
			PlayerController->bShowMouseCursor = false;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("InventoryWidget->IsInViewport() is false"));
		InventoryWidget->AddToViewport();
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (PlayerController != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("PlayerContorller is exist, Game And UI"));
			FInputModeGameAndUI InputMode;
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			InputMode.SetHideCursorDuringCapture(false);
			PlayerController->SetInputMode(InputMode);
			PlayerController->bShowMouseCursor = true;
		}
	}
}

void AGameCharacter::BeginPlay()
{
	Super::BeginPlay();

	/*
	UUserWidget* Widget = CreateWidget<UUserWidget>(UGameplayStatics::GetPlayerController(this, 0), UUWInventory::StaticClass());
	InventoryWidget = Cast<UUWInventory>(Widget);
	
	if (InventoryWidget == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Character InvenWidget fail"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Character InvenWidget succeed"));
	}*/

	if (IsValid(MainWidgetClass))
	{
		InventoryWidget = Cast<UUWInventory>(CreateWidget(GetWorld(), MainWidgetClass));

		if (InventoryWidget)
		{
			InventoryWidget->AddToViewport();
		}
	}

	//InventoryWidget->TileSize = 50.0f;

	//InventoryWidget->ACInventory = InventoryComponent;

	//InventoryWidget->AddToViewport();
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
