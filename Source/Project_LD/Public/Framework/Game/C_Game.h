// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/ACInventoryComponent.h"
#include "Framework/Character/AppearanceCharacter.h"
#include "C_Game.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_LD_API AC_Game : public AAppearanceCharacter
{
	GENERATED_BODY()

public:
	AC_Game();
	~AC_Game();
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* mGameCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* mCameraBoom;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UACInventoryComponent* mInventoryComponent;

public:
	UFUNCTION()
	void InteractItem();
};
