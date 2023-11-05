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

	InputComponent->BindAxis("CameraZoom(Player)", this, &AMovementController::OnSetCameraZoomAxis);
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

void AMovementController::MoveToMouseCursor(AActor* inHitActor, FHitResult inHitResult)
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
	const float halfHeight = character->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

	mDestLocation = inHitResult.ImpactPoint;
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
	newMovementLocation->set_z(mDestLocation.Z + halfHeight);

	SendBufferPtr pakcetBuffer = FGamePacketHandler::MakeSendBuffer(controller, movementPacket);
	controller->Send(pakcetBuffer);

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, mDestLocation);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), mMouseCursorParticle, FVector(mDestLocation.X, mDestLocation.Y, (mDestLocation.Z + 1.0f)), FRotator::ZeroRotator, true);
}

void AMovementController::OnTeleport(const FVector& DestLocation)
{
	ACharacter* character = Cast<ACharacter>(this->GetPawn());
	if (nullptr == character)
	{
		return;
	}

	mIsLocationCorrection = false;
	mTargetLoction = DestLocation;
	character->SetActorLocation(DestLocation, false, nullptr, ETeleportType::ResetPhysics);
	this->StopMovement();

	UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("PC OnTeleport")), ELogLevel::Warning);
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

	FVector		direction = inNewMovementLocation - inOldMovementLocation;
	FRotator	rotation = direction.Rotation();
	FVector		foward = rotation.Quaternion().GetForwardVector();

	FVector curLocation;
	FVector deadReckoningLocation;
	FVector overDeadReckoningLocation;

	FVector velocity = foward * speed;
	float duration = inTime / 1000.0f;
	

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
		curLocation					= character->GetActorLocation();
		deadReckoningLocation		= inOldMovementLocation + (velocity * duration);
		overDeadReckoningLocation	= inOldMovementLocation + (velocity * 0.2f);

		float nowDistance = FVector::Dist(curLocation, deadReckoningLocation);
		float overDistance = FVector::Dist(curLocation, overDeadReckoningLocation);

		if (nowDistance > overDistance)
		{
			mIsLocationCorrection = true;
			mTargetLoction = deadReckoningLocation;
			mCorrectionVelocity = 0.1f;
		}

		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, inNewMovementLocation);
	}

	//mIsRotationCorrection = true;
	//mTargetRotation = rotation;

	//UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("cur[%ws], dead[%ws], old[%ws], new[%ws], distance[%f], duration[%f]"), *curLocation.ToString(), *deadReckoningLocation.ToString(), *inOldMovementLocation.ToString(), *inNewMovementLocation.ToString(), distance, duration), ELogLevel::Error);

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
