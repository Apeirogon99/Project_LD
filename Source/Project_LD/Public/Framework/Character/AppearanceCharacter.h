// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Network/NetworkCharacter.h"
#include "AppearanceCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_LD_API AAppearanceCharacter : public ANetworkCharacter
{
	GENERATED_BODY()
	
public:
	AAppearanceCharacter();
	virtual ~AAppearanceCharacter();

public:
	void InitializeAppearance();

	void UpdateCharacterEquipment(const FCharacterEquipment& InCharacterEquipment);
	void UpdateCharacterAppearnce(const FCharacterAppearance& InCharacterAppearance);
	void UpdateCharacterPose(const ECharacterPose InCharacterPose);

	void SetSkeletalPartColor(USkeletalMeshComponent* inMesh, const FString& inParamterName, int32 inIndex, uint32 inColor);
	void SetSkeletalPartMesh(USkeletalMeshComponent* InMeshPart, int32 InMeshIndex);

public:
	FLinearColor GetMeshColor(const EAppearance InAppearance);

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Equipment")
		USkeletalMeshComponent* mHair;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Equipment")
		USkeletalMeshComponent* mHelmet;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Equipment")
		USkeletalMeshComponent* mShoulders;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Equipment")
		USkeletalMeshComponent* mChest;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Equipment")
		USkeletalMeshComponent* mBracers;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Equipment")
		USkeletalMeshComponent* mHands;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Equipment")
		USkeletalMeshComponent* mPants;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Equipment")
		USkeletalMeshComponent* mBoots;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Weapon")
		USkeletalMeshComponent* mBack_2HL;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Weapon")
		USkeletalMeshComponent* mBack_Shield;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Weapon")
		USkeletalMeshComponent* mBack_WeaponL;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Weapon")
		USkeletalMeshComponent* mBack_WeaponR;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Weapon")
		USkeletalMeshComponent* mBack_Bow;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Weapon")
		USkeletalMeshComponent* mQuiver;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Weapon")
		USkeletalMeshComponent* mWeapon_R_Arrow;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Weapon")
		USkeletalMeshComponent* mWeapon_Shield;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Weapon")
		USkeletalMeshComponent* mWeapon_L;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Weapon")
		USkeletalMeshComponent* mWeapon_R;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Weapon")
		USkeletalMeshComponent* mHip_L;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Weapon")
		USkeletalMeshComponent* mHip_R;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Animation")
	TArray<UAnimationAsset*> mCharacterPoses;
};
