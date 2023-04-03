// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <Struct/Game/CharacterDatas.h>
#include "NetworkCharacter.generated.h"

UCLASS()
class PROJECT_LD_API ANetworkCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ANetworkCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	void InitializeCharacter(const FCharacterAppearance& InCharacterAppearance, const FCharacterEquipment& InCharacterEquipment);
	void ConstructCharacter();

	//void UpdateCharacterData(const FCharacterDatas& InCharacterDatas);
	void UpdateCharacterEquipment(const FCharacterEquipment& InCharacterEquipment);
	void UpdateCharacterAppearnce(const FCharacterAppearance& InCharacterAppearance);
	void UpdateAnimationAsset(UAnimationAsset* InAnimationAsset);
	FLinearColor GetMeshColor(const EAppearance InAppearance);

protected:
	USkeletalMeshComponent* GetPartInformation(const EEquipment InPart, FString& OutParamterName, int32& OutIndex);
	void SetSkeletalPartColor(USkeletalMeshComponent* inMesh, const FString& inParamterName, int32 inIndex, uint32 inColor);
	void SetSkeletalPartMesh(USkeletalMeshComponent* InMeshPart, int32 InMeshIndex);

public:
	FCharacterAppearance	mCharacterAppearance;
	FCharacterEquipment		mChracterEquipment;

//Appearance Skin
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Skin")
		USkeletalMeshComponent* mEars;								  
																	  
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Skin")
		USkeletalMeshComponent* mFeet;								  
																	  
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Equipment")
		USkeletalMeshComponent* mHair;								  
																	  
/*	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Skin")
		USkeletalMeshComponent* mFacials_01;		*/				   
																	   
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Skin")
		USkeletalMeshComponent* mFacials;						   
																	   
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Equipment")
		USkeletalMeshComponent* mHelmet;							   
																	   
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Equipment")
		USkeletalMeshComponent* mShoulders;							   
																	   
	//UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Skin")
	//	USkeletalMeshComponent* mSkirt;		

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Skin")
		USkeletalMeshComponent* mPants;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Equipment")
		USkeletalMeshComponent* mPantsAdd;
																	  
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Skin")
		USkeletalMeshComponent* mLegs;								   
																	   
/*	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Skin")
		USkeletalMeshComponent* mLegsAdd;	*/						   
																	   
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Skin")
		USkeletalMeshComponent* mHands;								  
																	  
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Equipment")
		USkeletalMeshComponent* mHandsAdd;							   
																	   
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Skin")
		USkeletalMeshComponent* mChest;								   
																	   
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Equipment")
		USkeletalMeshComponent* mChestAdd;							  
																	  
/*	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Skin")
		USkeletalMeshComponent* mCape;		*/						  
																	  
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Skin")
		USkeletalMeshComponent* mBracers;							  
																	  
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Equipment")
		USkeletalMeshComponent* mBracersAdd;						  
																	  
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Equipment")
		USkeletalMeshComponent* mBoots;								   
																	   
/*	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Skin")
		USkeletalMeshComponent* mBelt;		*/						   

	//UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Skin")
	//	USkeletalMeshComponent* mTabard;

//Appearance Weapon
public:
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
};
