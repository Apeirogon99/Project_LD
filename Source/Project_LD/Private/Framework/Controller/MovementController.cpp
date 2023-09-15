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
#include <GameFramework/CharacterMovementComponent.h>
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
	mTeleport = false;
	mCorrectionVelocity = 0.0f;
	mTeleportCool = 0.0f;
}

AMovementController::~AMovementController()
{
}

bool AMovementController::OnTick()
{
	Super::OnTick();

	if (mIsMoveToMouseCursor == true)
	{
		MoveToMouseCursor();
	}

	return true;
}

void AMovementController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

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

	MoveToMouseCursor();
}

void AMovementController::OnSetDestinationReleased()
{
	mIsMoveToMouseCursor = false;

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), mMouseCursorParticle, FVector(mDestLocation.X, mDestLocation.Y, (mDestLocation.Z + 1.0f)), FRotator::ZeroRotator, true);
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

		if (character->GetCanMove() == false)
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

void AMovementController::OnTeleport_Implementation(const FVector& DestLocation)
{
	ACharacter* character = Cast<ACharacter>(this->GetPawn());
	if (nullptr == character)
	{
		return;
	}

	mTargetLoction = DestLocation;
	mIsLocationCorrection = false;
	mTeleport = true;

	const FRotator& rotation = character->GetActorRotation();

	character->TeleportTo(DestLocation, rotation, false, false);
}

void AMovementController::SetNewMoveDestination(FVector& DestLocation)
{

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
	const float halfHeight	= character->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

	mDestLocation = FVector(DestLocation.X, DestLocation.Y, DestLocation.Z + halfHeight);
	mCurLocation = character->GetActorLocation();

	Protocol::C2S_MovementCharacter movementPacket;
	movementPacket.set_timestamp(controller->GetServerTimeStamp());

	FVector pawnLocation = character->GetActorLocation();
	Protocol::SVector* oldMovementLocation = movementPacket.mutable_cur_location();
	oldMovementLocation->set_x(pawnLocation.X);
	oldMovementLocation->set_y(pawnLocation.Y);
	oldMovementLocation->set_z(pawnLocation.Z);

	Protocol::SVector* newMovementLocation = movementPacket.mutable_move_location();
	newMovementLocation->set_x(mDestLocation.X);
	newMovementLocation->set_y(mDestLocation.Y);
	newMovementLocation->set_z(mDestLocation.Z);

	SendBufferPtr pakcetBuffer = FGamePacketHandler::MakeSendBuffer(controller, movementPacket);
	controller->Send(pakcetBuffer);

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);

}

void AMovementController::SendMove()
{
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

	Protocol::C2S_MovementCharacter movementPacket;
	movementPacket.set_timestamp(controller->GetServerTimeStamp());

	FVector pawnLocation = character->GetActorLocation();
	Protocol::SVector* oldMovementLocation = movementPacket.mutable_cur_location();
	oldMovementLocation->set_x(pawnLocation.X);
	oldMovementLocation->set_y(pawnLocation.Y);
	oldMovementLocation->set_z(pawnLocation.Z);

	Protocol::SVector* newMovementLocation = movementPacket.mutable_move_location();
	newMovementLocation->set_x(mDestLocation.X);
	newMovementLocation->set_y(mDestLocation.Y);
	newMovementLocation->set_z(mDestLocation.Z);

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
	FCharacterStats stats = playerState->GetCharacterStats();
	float speed = stats.GetCurrentStats().GetMovementSpeed();

	character->GetCharacterMovement()->MaxWalkSpeed = speed;

	FVector	direction = inNewMovementLocation - inOldMovementLocation;
	FRotator rotation = direction.Rotation();
	FVector foward = rotation.Quaternion().GetForwardVector();

	FVector velocity = foward * speed;
	float	duration = fabs(inTime / 1000.0f);

	FVector deadReckoningLocation = inOldMovementLocation + (velocity * duration);

	FVector curLocation = character->GetActorLocation();
	float distance = FVector::Dist(inOldMovementLocation, inNewMovementLocation);
	if (distance <= 1.0f)
	{
		mIsLocationCorrection = false;
		mTargetLoction = inNewMovementLocation;
		character->SetActorLocation(inNewMovementLocation);
		this->StopMovement();
	}
	else
	{
		distance = FVector::Dist(curLocation, deadReckoningLocation);
		if (distance > 1.0f)
		{
			mIsLocationCorrection = true;
			mTargetLoction = deadReckoningLocation;
			mCorrectionVelocity = 0.01f;
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, inNewMovementLocation);
		}
	}

	//mIsRotationCorrection = true;
	//mTargetRotation = rotation;

	UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("cur[%ws], dead[%ws], old[%ws], new[%ws], distance[%f], duration[%f]"), *curLocation.ToString(), *deadReckoningLocation.ToString(), *inOldMovementLocation.ToString(), *inNewMovementLocation.ToString(), distance, duration), ELogLevel::Error);

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

	FVector correctionLocation = FMath::VInterpTo(curLocation, mTargetLoction, inDeltaTime, mCorrectionVelocity);

	float distance = FVector::Dist(curLocation, correctionLocation);
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

	FRotator curRotation = pawn->GetActorRotation();
	float	velocity = 1.0f;

	FRotator correctionRotation = FMath::Lerp(curRotation, mTargetRotation, velocity * inDeltaTime);

	if (correctionRotation.Equals(mTargetRotation, 0.1f))
	{
		pawn->SetActorRotation(mTargetRotation, ETeleportType::ResetPhysics);
		mIsRotationCorrection = false;
	}
	else
	{
		pawn->SetActorRotation(correctionRotation, ETeleportType::ResetPhysics);
	}
}

void AMovementController::StopMovementController(const FVector& inStopLocation)
{
	ACharacter* character = Cast<ACharacter>(this->GetPawn());
	if (nullptr == character)
	{
		return;
	}

	mIsLocationCorrection = false;
	mTargetLoction = inStopLocation;
	character->SetActorLocation(inStopLocation);

	this->StopMovement();
}
