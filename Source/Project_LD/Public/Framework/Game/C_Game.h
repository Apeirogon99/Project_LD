// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/ACInventoryComponent.h"
#include "Framework/Character/AppearanceCharacter.h"
#include "NC_Game.h"
#include "C_Game.generated.h"

/**
 * 
 */
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class PROJECT_LD_API AC_Game : public ANC_Game
{
	GENERATED_BODY()

public:
	AC_Game();
	~AC_Game();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Destroyed() override;

public:
	void SetIsZoom(const bool& InIsZoom) { bIsZoom = InIsZoom; }

public:
	FORCEINLINE bool GetIsZoom() const { return bIsZoom; }

public:
	UFUNCTION(BlueprintNativeEvent, Category = "Camera Control")
	void OnAttackCameraZoomIn();
	virtual void OnAttackCameraZoomIn_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Camera Control")
	void OnAttackCameraZoomOut();
	virtual void OnAttackCameraZoomOut_Implementation();

public:
	UCameraComponent* GetCameraComponent() { return mGameCameraComponent; }

protected:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* mGameCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* mCameraBoom;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Zoom", meta = (AllowPrivateAccess = "true"))
		bool bIsZoom;
};
