// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/ACInventoryComponent.h"
#include "Framework/Character/AppearanceCharacter.h"
#include "C_Game.generated.h"

/**
 * 
 */
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class PROJECT_LD_API AC_Game : public AAppearanceCharacter
{
	GENERATED_BODY()

public:
	AC_Game();
	~AC_Game();
	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* mGameCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* mCameraBoom;

public:
	UFUNCTION()
	void InteractItem();

	UCameraComponent* GetCameraComponent() { return mGameCameraComponent; }
};
