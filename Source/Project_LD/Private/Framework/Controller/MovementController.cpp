// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Controller/MovementController.h"
#include "MovementController.h"

#include <Network/NetworkUtils.h>
#include <Protobuf/Handler/FClientPacketHandler.h>
#include <Protobuf/Handler/FGamePacketHandler.h>

#include <Network/NetworkCharacter.h>
#include <Framework/Game/C_Game.h>
#include <Framework/Game/PS_Game.h>
#include "Components/CapsuleComponent.h"
#include <GameFramework/PawnMovementComponent.h>
#include "Framework/AnimInstance/AI_PlayerCharacter.h"

#include <Framework/Character/AppearanceCharacter.h>
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include <Kismet/GameplayStatics.h>
#include <Interface/InteractiveInterface.h>
#include <Kismet/KismetMathLibrary.h>

AMovementController::AMovementController()
{
	IsMoveToMouseCursor = false;
	IsCorrection = false;
}

AMovementController::~AMovementController()
{
}

void AMovementController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (IsMoveToMouseCursor)
	{
		IsMoveToMouseCursor = false;
		MoveToMouseCursor();
	}

	if (IsCorrection)
	{
		MoveCorrection(DeltaTime);
	}
}

void AMovementController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination(Player)", IE_Pressed, this, &AMovementController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination(Player)", IE_Released, this, &AMovementController::OnSetDestinationReleased);
	InputComponent->BindAxis("CameraZoom(Player)", this, &AMovementController::OnSetCameraZoomAxis);
}

void AMovementController::OnSetDestinationPressed()
{
	IsMoveToMouseCursor = true;
}

void AMovementController::OnSetDestinationReleased()
{
	IsMoveToMouseCursor = false;
}

void AMovementController::OnSetCameraZoomAxis(const float inValue)
{
}

void AMovementController::SwitchMovementMode()
{
	bShowMouseCursor = true;
	IsMoveToMouseCursor = false;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AMovementController::MoveToMouseCursor()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (false == Hit.bBlockingHit)
	{
		return;
	}

	if (Hit.Actor.Get()->Tags.Num() > 0)
	{
		FName actortag = Hit.Actor.Get()->Tags[0];
		if (actortag == FName("Ground"))
		{
			SetNewMoveDestination(Hit.ImpactPoint);
		}
		else
		{
			if (Hit.Actor->GetClass()->ImplementsInterface(UInteractiveInterface::StaticClass()))
			{
				AC_Game* character = Cast<AC_Game>(GetCharacter());
				if (character == nullptr)
				{
					return;
				}
				Cast<IInteractiveInterface>(Hit.Actor)->Interactive(character);
				if (actortag == FName("Enemy"))
				{
					auto animInstance = Cast<UAI_PlayerCharacter>(GetCharacter()->GetMesh()->GetAnimInstance());
					animInstance->PlayAttackMontage();
				}
			}
		}
	}
}

void AMovementController::SetNewMoveDestination(FVector& DestLocation)
{

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), mMouseCursorParticle, FVector(DestLocation.X, DestLocation.Y, (DestLocation.Z + 1.0f)), FRotator::ZeroRotator, true);

	//TODO: 서버에게 보낼 값
	ANetworkController* controller = Cast<ANetworkController>(this);
	if (nullptr == controller)
	{
		return;
	}

	ACharacter* character = Cast<ACharacter>(this->GetPawn());
	if (nullptr == character)
	{
		return;
	}

	const float halfHeight	= character->GetCapsuleComponent()->GetScaledCapsuleHalfHeight() + 2.0f;
	DestLocation.Z += halfHeight;

	FVector		direction = DestLocation - character->GetActorLocation();
	FRotator	rotation = direction.Rotation();
	FVector		foward = UKismetMathLibrary::GetForwardVector(rotation);

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);

	
	Protocol::C2S_MovementCharacter movementPacket;
	const int64 serverTimeStamp = controller->GetServerTimeStamp();
	movementPacket.set_timestamp(serverTimeStamp);

	FVector pawnLocation = character->GetActorLocation();
	Protocol::SVector* oldMovementLocation = movementPacket.mutable_cur_location();
	oldMovementLocation->set_x(pawnLocation.X);
	oldMovementLocation->set_y(pawnLocation.Y);
	oldMovementLocation->set_z(pawnLocation.Z);

	Protocol::SVector* newMovementLocation = movementPacket.mutable_move_location();
	newMovementLocation->set_x(DestLocation.X);
	newMovementLocation->set_y(DestLocation.Y);
	newMovementLocation->set_z(DestLocation.Z);

	SendBufferPtr pakcetBuffer = FGamePacketHandler::MakeSendBuffer(controller, movementPacket);
	controller->Send(pakcetBuffer);
	

}

void AMovementController::MoveDestination(const FVector inOldMovementLocation, const FVector inNewMovementLocation, const int64 inTime)
{

	ACharacter* character = Cast<ACharacter>(this->GetPawn());
	if (nullptr == character)
	{
		return;
	}

	ANPS_Game* playerState = this->GetPlayerState<ANPS_Game>();
	if (nullptr == playerState)
	{
		return;
	}

	FVector	direction = inNewMovementLocation - inOldMovementLocation;
	direction.Normalize();

	FVector velocity = direction * playerState->GetCharacterStats().GetCurrentStats().GetMovementSpeed();
	float	duration = inTime / 1000.0f;

	FVector deadReckoningLocation = inOldMovementLocation + (velocity * duration);

	//현재 위치와 비교하여 차이가 얼마나 나는지 판단
	FVector curLocation = character->GetActorLocation();
	float locationDistance = FVector::Dist2D(curLocation, deadReckoningLocation);
	if (locationDistance >= 5.0f)
	{
		IsCorrection = true;
		mTargetLoction = inOldMovementLocation;
	}
	else
	{
		IsCorrection = true;
		mTargetLoction = deadReckoningLocation;
	}

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, inNewMovementLocation);
}

void AMovementController::MoveCorrection(const float inDeltaTime)
{
	APawn* pawn = this->GetPawn();
	if (nullptr == pawn)
	{
		return;
	}

	if (false == IsCorrection)
	{
		return;
	}

	FVector curLocation = pawn->GetActorLocation();
	float	velocity = 3.0f;

	FVector correctionLocation = FMath::VInterpTo(curLocation, mTargetLoction, inDeltaTime, velocity);

	float distance = FVector::Dist2D(curLocation, correctionLocation);
	if (distance <= 1.0f)
	{
		pawn->SetActorLocation(mTargetLoction, false, nullptr, ETeleportType::ResetPhysics);
		IsCorrection = false;
	}
	else
	{
		pawn->SetActorLocation(correctionLocation, false, nullptr, ETeleportType::ResetPhysics);
	}

}