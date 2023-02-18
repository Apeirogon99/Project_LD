// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <Struct/Game/CharacterDatas.h>
#include "C_Dummy.generated.h"

class USkeletalMeshComponent;
class UStaticMeshComponent;

UCLASS()
class PROJECT_LD_API AC_Dummy : public ACharacter
{
	GENERATED_BODY()

public:
	AC_Dummy();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
	USkeletalMeshComponent* mBodyMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
	UStaticMeshComponent*	mHairMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
	UStaticMeshComponent*	mEyeMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
	UStaticMeshComponent*	mEyebrowMesh;

public:
	UFUNCTION(BlueprintCallable)
		void SetTrib(ETribe inTrib);

	UFUNCTION(BlueprintCallable)
		void SetClass(EClass inClass);

	UFUNCTION()
		void SetPartColor(EPart inPart, FLinearColor inColor, int32 inIndex = 0);

	UFUNCTION()
		void SetCharacterDatas(const FCharacterDatas& inCharacterDatas);

	UFUNCTION()
		void SetAnimation(UAnimationAsset* inAnimationAsset);

	UFUNCTION()
		EClass GetClass();

	UFUNCTION()
		ETribe GetTribe();

	UFUNCTION()
		FLinearColor GetPartColor(EPart inPart, int32 inIndex = 0);

	UFUNCTION()
		uint32 GetPartColorToInt(EPart inPart, int32 inIndex = 0);

protected:
	UFUNCTION()
		void SetStaticPartColor(UStaticMeshComponent* inPartMesh, const FString& inParameterName, FLinearColor inColor, int32 inIndex = 0);

	UFUNCTION()
		void SetSkeletalPartColor(USkeletalMeshComponent* inPartMesh, const FString& inParameterName, FLinearColor inColor, int32 inIndex = 0);

	UFUNCTION()
		FLinearColor GetStaticPartColor(UStaticMeshComponent* inPartMesh, const FString& inParameterName, int32 inIndex = 0);

	UFUNCTION()
		FLinearColor GetSkeletalPartColor(USkeletalMeshComponent* inPartMesh, const FString& inParameterName, int32 inIndex = 0);

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Man")
	TArray<USkeletalMesh*> mManBodys;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Man")
	TArray <UStaticMesh*> mManHair;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Man")
	TArray <UStaticMesh*> mManEye;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Man")
	TArray <UStaticMesh*> mManEyebrow;

	//
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Woman")
		TArray<USkeletalMesh*> mWomanBodys;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Woman")
		TArray <UStaticMesh*> mWomanHair;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Woman")
		TArray <UStaticMesh*> mWomanEye;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Woman")
		TArray <UStaticMesh*> mWomanEyebrow;

	//
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Orc")
		TArray<USkeletalMesh*> mOrcBodys;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Orc")
		TArray <UStaticMesh*> mOrcHair;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Orc")
		TArray <UStaticMesh*> mOrcEye;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Orc")
		TArray <UStaticMesh*> mOrcEyebrow;

private:
	EClass mClass;
	ETribe mTribe;
	FCharacterDatas mCharacterDatas;
};
