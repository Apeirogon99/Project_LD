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
	virtual void InitializeCharacterData(const FCharacterDatas& InCharacterDatas, const FCharacterAppearance& InCharacterAppearance);
	
protected:
	void UpdateCharacterData(const FCharacterDatas& InCharacterDatas);
	void UpdateCharacterAppearnce(const FCharacterAppearance& InCharacterAppearance);

	bool GetPartInformation(const EPart InPart, USkeletalMeshComponent* OutMeshPart, FString OutParamterName, int32 OutIndex);
	void SetSkeletalPartColor(const EPart InPart, uint32 InColor);
	FLinearColor GetStaticPartColor(const EPart InPart);

	void SetSkeletalPartMesh(USkeletalMeshComponent* InMeshPart, int32 InMeshIndex);

protected:
	FCharacterDatas			mCharacterData;
	FCharacterAppearance	mCharacterAppearance;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Skin")
		TArray<USkeletalMesh*> mSkeletalMeshs;

//Appearance Skin
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Skin")
		USkeletalMeshComponent* mEars;								  
																	  
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Skin")
		USkeletalMeshComponent* mFeet;								  
																	  
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Skin")
		USkeletalMeshComponent* mHair;								  
																	  
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Skin")
		USkeletalMeshComponent* mFacials_01;						   
																	   
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Skin")
		USkeletalMeshComponent* mFacials_02;						   
																	   
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Skin")
		USkeletalMeshComponent* mHelmet;							   
																	   
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Skin")
		USkeletalMeshComponent* mShoulders;							   
																	   
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Skin")
		USkeletalMeshComponent* mSkirt;								  
																	  
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Skin")
		USkeletalMeshComponent* mLegs;								   
																	   
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Skin")
		USkeletalMeshComponent* mLegsAdd;							   
																	   
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Skin")
		USkeletalMeshComponent* mHands;								  
																	  
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Skin")
		USkeletalMeshComponent* mHandsAdd;							   
																	   
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Skin")
		USkeletalMeshComponent* mChest;								   
																	   
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Skin")
		USkeletalMeshComponent* mChestAdd;							  
																	  
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Skin")
		USkeletalMeshComponent* mCape;								  
																	  
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Skin")
		USkeletalMeshComponent* mBracers;							  
																	  
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Skin")
		USkeletalMeshComponent* mBracersAdd;						  
																	  
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Skin")
		USkeletalMeshComponent* mBoots;								   
																	   
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Skin")
		USkeletalMeshComponent* mBelt;								   

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance | Skin")
		USkeletalMeshComponent* mTabard;

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
