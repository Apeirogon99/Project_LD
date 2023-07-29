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
	mIsMoveToMouseCursor	= false;
	mIsLocationCorrection	= false;
	mIsRotationCorrection	= false;
}

AMovementController::~AMovementController()
{
}

void AMovementController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (mIsMoveToMouseCursor)
	{
		mIsMoveToMouseCursor = false;
		MoveToMouseCursor();
	}

	if (mIsLocationCorrection)
	{
		MoveCorrection(DeltaTime);
	}

	if (mIsRotationCorrection)
	{
		RotationCorrection(DeltaTime);
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
	mIsMoveToMouseCursor = true;
}

void AMovementController::OnSetDestinationReleased()
{
	mIsMoveToMouseCursor = false;
}

void AMovementController::OnSetCameraZoomAxis(const float inValue)
{
}

void AMovementController::SwitchMovementMode()
{
	bShowMouseCursor = true;
	mIsMoveToMouseCursor = false;
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
		ANC_Game* character = Cast<ANC_Game>(GetCharacter());
		if (character == nullptr)
		{
			return;
		}

		FName actortag = Hit.Actor.Get()->Tags[0];
		if (actortag == FName("Enemy"))
		{
			if (Hit.Actor->GetClass()->ImplementsInterface(UInteractiveInterface::StaticClass()))
			{
				Cast<IInteractiveInterface>(Hit.Actor)->Interactive(character);
			}
		}
		else
		{
			if (character->GetIsAttack() == false)
			{
				if (actortag == FName("Ground"))
				{
					//Ground
					SetNewMoveDestination(Hit.ImpactPoint);
				}
				else
				{
					if (Hit.Actor->GetClass()->ImplementsInterface(UInteractiveInterface::StaticClass()))
					{
						//Interactive Things
						Cast<IInteractiveInterface>(Hit.Actor)->Interactive(character);
					}
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

void AMovementController::MoveDestination(const FVector& inOldMovementLocation, const FVector& inNewMovementLocation, const int64& inTime)
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
	if (locationDistance >= 1.0f)
	{
		mIsLocationCorrection = true;
		mTargetLoction = inOldMovementLocation;
	}
	else
	{
		mIsLocationCorrection = true;
		mTargetLoction = deadReckoningLocation;
	}

	//UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("cur[%ws], dead[%ws], new[%ws] distance[%f]"), *inOldMovementLocation.ToString(), *deadReckoningLocation.ToString(), *inNewMovementLocation.ToString(), locationDistance), ELogLevel::Error);

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, inNewMovementLocation);
}

void AMovementController::MoveCorrection(const float inDeltaTime)
{
	APawn* pawn = this->GetPawn();
	if (nullptr == pawn)
	{
		return;
	}

	if (false == mIsLocationCorrection)
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
		mIsLocationCorrection = false;
	}
	else
	{
		pawn->SetActorLocation(correctionLocation, false, nullptr, ETeleportType::ResetPhysics);
	}

}

void AMovementController::RotationDestination(const FRotator& inNewRotation, const int64& inTime)
{
}

void AMovementController::RotationCorrection(const float inDeltaTime)
{
	APawn* pawn = this->GetPawn();
	if (nullptr == pawn)
	{
		return;
	}

	if (false == mIsRotationCorrection)
	{
		return;
	}

	FRotator	curRotation = pawn->GetActorRotation();
	float		interpSpeed = 3.0f;

	FRotator correctionRotation = FMath::RInterpTo(curRotation, mTargetRotation, inDeltaTime, interpSpeed);

	float rotationDelta = correctionRotation.Pitch - curRotation.Pitch;
	if (rotationDelta <= 1.0f)
	{
		pawn->SetActorRotation(mTargetRotation, ETeleportType::ResetPhysics);
		mIsRotationCorrection = false;
	}
	else
	{
		pawn->SetActorRotation(correctionRotation, ETeleportType::ResetPhysics);
	}
}
