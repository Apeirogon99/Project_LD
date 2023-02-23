// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/NetworkCharacter.h"
#include <Network/NetworkUtils.h>

// Sets default values
ANetworkCharacter::ANetworkCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Appearance
	mEars			= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mEars"));
	mFeet			= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mFeet"));
	mHair			= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mHair"));
	mFacials_01		= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mFacials_01"));
	mFacials_02		= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mFacials_02"));
	mHelmet			= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mHelmet"));
	mShoulders		= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mShoulders"));
	mSkirt			= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mSkirt"));
	mLegs			= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mLegs"));
	mLegsAdd		= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mLegsAdd"));
	mHands			= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mHands"));
	mHandsAdd		= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mHandsAdd"));
	mChest			= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mChest"));
	mChestAdd		= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mChestAdd"));
	mCape			= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mCape"));
	mBracers		= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mBracers"));
	mBracersAdd		= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mBracersAdd"));
	mBoots			= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mBoots"));
	mBelt			= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mBelt"));
	mTabard			= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mTabard"));

	//Weapon
	mBack_2HL		= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mBack_2HL"));
	mBack_Shield	= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mBack_Shield"));
	mBack_WeaponL	= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mBack_WeaponL"));
	mBack_WeaponR	= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mBack_WeaponR"));
	mBack_Bow		= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mBack_Bow"));
	mQuiver			= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mQuiver"));
	mWeapon_R_Arrow = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mWeapon_R_Arrow"));
	mWeapon_Shield	= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mWeapon_Shield"));
	mWeapon_L		= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mWeapon_L"));
	mWeapon_R		= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mWeapon_R"));
	mHip_L			= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mHip_L"));
	mHip_R			= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mHip_R"));

	USkeletalMeshComponent* meshRoot = GetMesh();
	if (meshRoot)
	{
		//Appearance
		mEars->SetupAttachment(meshRoot);
		mFeet->SetupAttachment(meshRoot);
		mHair->SetupAttachment(meshRoot);
		mFacials_01->SetupAttachment(meshRoot);
		mFacials_02->SetupAttachment(meshRoot);
		mHelmet->SetupAttachment(meshRoot);
		mShoulders->SetupAttachment(meshRoot);
		mSkirt->SetupAttachment(meshRoot);
		mLegs->SetupAttachment(meshRoot);
		mLegsAdd->SetupAttachment(meshRoot);
		mHands->SetupAttachment(meshRoot);
		mHandsAdd->SetupAttachment(meshRoot);
		mChest->SetupAttachment(meshRoot);
		mChestAdd->SetupAttachment(meshRoot);
		mCape->SetupAttachment(meshRoot);
		mBracers->SetupAttachment(meshRoot);
		mBracersAdd->SetupAttachment(meshRoot);
		mBoots->SetupAttachment(meshRoot);
		mBelt->SetupAttachment(meshRoot);
		mTabard->SetupAttachment(meshRoot);

		//Weapon
		mBack_2HL->SetupAttachment(meshRoot);
		mBack_Shield->SetupAttachment(meshRoot);
		mBack_WeaponL->SetupAttachment(meshRoot);
		mBack_WeaponR->SetupAttachment(meshRoot);
		mBack_Bow->SetupAttachment(meshRoot);
		mQuiver->SetupAttachment(meshRoot);
		mWeapon_R_Arrow->SetupAttachment(meshRoot);
		mWeapon_Shield->SetupAttachment(meshRoot);
		mWeapon_L->SetupAttachment(meshRoot);
		mWeapon_R->SetupAttachment(meshRoot);
		mHip_L->SetupAttachment(meshRoot);
		mHip_R->SetupAttachment(meshRoot);

	}
}

// Called when the game starts or when spawned
void ANetworkCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ANetworkCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANetworkCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANetworkCharacter::InitializeCharacter(const FCharacterDatas& InCharacterDatas, const FCharacterAppearance& InCharacterAppearance)
{
	UpdateCharacterData(InCharacterDatas);
	UpdateCharacterAppearnce(InCharacterAppearance);
	UpdateCharacterVisual(InCharacterAppearance);
}

void ANetworkCharacter::UpdateCharacterData(const FCharacterDatas& InCharacterDatas)
{
	mCharacterData = InCharacterDatas;
}

void ANetworkCharacter::UpdateCharacterVisual(const FCharacterAppearance& InCharacterAppearance)
{
	SetSkeletalPartColor(EPart::Boots,		InCharacterAppearance.mBodyColor);
	SetSkeletalPartColor(EPart::Bracers,	InCharacterAppearance.mBodyColor);
	SetSkeletalPartColor(EPart::Chest,		InCharacterAppearance.mBodyColor);
	SetSkeletalPartColor(EPart::Feet,		InCharacterAppearance.mBodyColor);
	SetSkeletalPartColor(EPart::Hands,		InCharacterAppearance.mBodyColor);
	SetSkeletalPartColor(EPart::Head,		InCharacterAppearance.mBodyColor);
	//SetSkeletalPartColor(EPart::Hair,		InCharacterAppearance.mHairColor);
	SetSkeletalPartColor(EPart::Eye,		InCharacterAppearance.mEyeColor);
	SetSkeletalPartColor(EPart::Eyebrow,	InCharacterAppearance.mEyeColor);
	SetSkeletalPartColor(EPart::Ears,		InCharacterAppearance.mBodyColor);
	SetSkeletalPartColor(EPart::Pants,		InCharacterAppearance.mBodyColor);

	mCharacterAppearance.mBodyColor = InCharacterAppearance.mBodyColor;
	mCharacterAppearance.mHairColor = InCharacterAppearance.mHairColor;
	mCharacterAppearance.mEyeColor = InCharacterAppearance.mEyeColor;

}

void ANetworkCharacter::UpdateCharacterAppearnce(const FCharacterAppearance& InCharacterAppearance)
{	

	USkeletalMeshComponent* meshRoot = GetMesh();
	int32 maxChild = meshRoot->GetNumChildrenComponents() + 1;

	for (int32 indexNumber = 0; indexNumber < maxChild; ++indexNumber)
	{
		int32 oldMesh = mCharacterAppearance.mMeshs[indexNumber];
		int32 newMesh = InCharacterAppearance.mMeshs[indexNumber];
		if (oldMesh != newMesh)
		{
			USkeletalMeshComponent* partMesh = nullptr;
			if (indexNumber == 0)
			{
				partMesh = meshRoot;
			}
			else
			{
				partMesh = StaticCast<USkeletalMeshComponent*>(meshRoot->GetChildComponent(indexNumber));
			}
			SetSkeletalPartMesh(partMesh, newMesh);
		}

		mCharacterAppearance.mMeshs[indexNumber] = InCharacterAppearance.mMeshs[indexNumber];
	}

	//SetSkeletalPartMesh(mEars,				InCharacterAppearance.mEars);
	//SetSkeletalPartMesh(mFeet,				InCharacterAppearance.mFeet);
	//SetSkeletalPartMesh(mHair,				InCharacterAppearance.mHair);
	//SetSkeletalPartMesh(mFacials_01,			InCharacterAppearance.mFacials_01);
	//SetSkeletalPartMesh(mFacials_02,			InCharacterAppearance.mFacials_02);
	//SetSkeletalPartMesh(mHelmet,				InCharacterAppearance.mHelmet);
	//SetSkeletalPartMesh(mShoulders,			InCharacterAppearance.mShoulders);
	//SetSkeletalPartMesh(mSkirt,				InCharacterAppearance.mSkirt);
	//SetSkeletalPartMesh(mLegs,				InCharacterAppearance.mLegs);
	//SetSkeletalPartMesh(mLegsAdd,				InCharacterAppearance.mLegsAdd);
	//SetSkeletalPartMesh(mHands,				InCharacterAppearance.mHands);
	//SetSkeletalPartMesh(mHandsAdd,			InCharacterAppearance.mHandsAdd);
	//SetSkeletalPartMesh(mChest,				InCharacterAppearance.mChest);
	//SetSkeletalPartMesh(mChestAdd,			InCharacterAppearance.mChestAdd);
	//SetSkeletalPartMesh(mCape,				InCharacterAppearance.mCape);
	//SetSkeletalPartMesh(mBracers,				InCharacterAppearance.mBracers);
	//SetSkeletalPartMesh(mBracersAdd,			InCharacterAppearance.mBracersAdd);
	//SetSkeletalPartMesh(mBoots,				InCharacterAppearance.mBoots);
	//SetSkeletalPartMesh(mBelt,				InCharacterAppearance.mBelt);
	//SetSkeletalPartMesh(mTabard,				InCharacterAppearance.mTabard);


	//SetSkeletalPartMesh(mBack_2HL,			InCharacterAppearance.mBack_2HL);
	//SetSkeletalPartMesh(mBack_Shield,			InCharacterAppearance.mBack_Shield);
	//SetSkeletalPartMesh(mBack_WeaponL,		InCharacterAppearance.mBack_WeaponL);
	//SetSkeletalPartMesh(mBack_WeaponR,		InCharacterAppearance.mBack_WeaponR);
	//SetSkeletalPartMesh(mBack_Bow,			InCharacterAppearance.mBack_Bow);
	//SetSkeletalPartMesh(mQuiver,				InCharacterAppearance.mQuiver);
	//SetSkeletalPartMesh(mWeapon_R_Arrow,		InCharacterAppearance.mWeapon_R_Arrow);
	//SetSkeletalPartMesh(mWeapon_Shield,		InCharacterAppearance.mWeapon_Shield);
	//SetSkeletalPartMesh(mWeapon_L,			InCharacterAppearance.mWeapon_L);
	//SetSkeletalPartMesh(mWeapon_R,			InCharacterAppearance.mWeapon_R);
	//SetSkeletalPartMesh(mHip_L,				InCharacterAppearance.mHip_L);
	//SetSkeletalPartMesh(mHip_R,				InCharacterAppearance.mHip_R);
}

void ANetworkCharacter::UpdateAnimationAsset(UAnimationAsset* InAnimationAsset)
{
	USkeletalMeshComponent* meshRoot = GetMesh();
	int32 maxChild = meshRoot->GetNumChildrenComponents();
	for (int32 indexNumber = 0; indexNumber < maxChild; ++indexNumber)
	{
		USkeletalMeshComponent* partMesh = StaticCast<USkeletalMeshComponent*>(meshRoot->GetChildComponent(indexNumber));
		if (partMesh)
		{
			partMesh->SetAnimationMode(EAnimationMode::AnimationSingleNode);
			partMesh->SetAnimation(InAnimationAsset);
		}
	}
}

USkeletalMeshComponent* ANetworkCharacter::GetPartInformation(const EPart InPart, FString& OutParamterName, int32& OutIndex)
{
	USkeletalMeshComponent* outMeshPart = nullptr;
	if (InPart == EPart::None)
	{
		UNetworkUtils::NetworkConsoleLog(TEXT("[ANetworkCharacter::GetPartInformation] Part is None"), ELogLevel::Error);
		return false;	
	}

	ETribe currentTribe = StaticCast<ETribe>(mCharacterData.mTribe);
	if (currentTribe == ETribe::None)
	{
		UNetworkUtils::NetworkConsoleLog(TEXT("[ANetworkCharacter::GetPartInformation] Tribe is None"), ELogLevel::Error);
		return false;
	}

	switch (InPart)
	{
	case EPart::Boots:
		outMeshPart = mBoots;
		OutParamterName = TEXT("BaseColor");
		OutIndex = 0;
		break;
	case EPart::Bracers:
		outMeshPart = mBracers;
		OutParamterName = TEXT("BaseColor");
		OutIndex = 0;
		break;
	case EPart::Chest:
		outMeshPart = mChest;
		OutParamterName = TEXT("BaseColor");
		OutIndex = 0;
		break;
	case EPart::Feet:
		outMeshPart = mFeet;
		OutParamterName = TEXT("BaseColor");
		OutIndex = 0;
		break;
	case EPart::Hands:
		outMeshPart = mHands;
		OutParamterName = TEXT("BaseColor");
		OutIndex = 0;
		break;
	case EPart::Head:
		outMeshPart = GetMesh();
		OutParamterName = TEXT("BaseColor");
		OutIndex = (currentTribe == ETribe::Woman ? 2 : 0);
		break;
	case EPart::Hair:
		outMeshPart = mHair;
		OutParamterName = TEXT("BaseColor");
		OutIndex = 0;
		break;
	case EPart::Eye:
		outMeshPart = GetMesh();
		OutParamterName = TEXT("BaseColor");
		OutIndex = (currentTribe == ETribe::Woman ? 1 : 1);
		break;
	case EPart::Eyebrow:
		outMeshPart = GetMesh();
		OutParamterName = TEXT("BaseColor");
		OutIndex = (currentTribe == ETribe::Woman ? 0 : 1);
		break;
	case EPart::Ears:
		outMeshPart = mEars;
		OutParamterName = TEXT("BaseColor");
		OutIndex = 0;
		break;
	case EPart::Pants:
		outMeshPart = mLegs;
		OutParamterName = TEXT("BaseColor");
		OutIndex = 0;
		break;
	default:
		break;
	}

	if (nullptr == outMeshPart)
	{
		return nullptr;
	}

	return outMeshPart;
}

void ANetworkCharacter::SetSkeletalPartColor(const EPart InPart, uint32 InColor)
{
	USkeletalMeshComponent* MeshPart = nullptr;
	FString					ParamterName = TEXT("");
	int32					Index = 0;

	FLinearColor partColor = UNetworkUtils::ConverLinearColor(InColor);
	if (GetPartColor(InPart) == partColor)
	{
		return;
	}

	MeshPart = GetPartInformation(InPart, ParamterName, Index);
	if (nullptr == MeshPart)
	{
		return;
	}

	UMaterialInstanceDynamic* materialDynamic = MeshPart->CreateDynamicMaterialInstance(Index);
	materialDynamic->SetVectorParameterValue(FName(*ParamterName), partColor);

	
}

FLinearColor ANetworkCharacter::GetPartColor(const EPart InPart)
{
	USkeletalMeshComponent* MeshPart = nullptr;
	FString					ParamterName = TEXT("");
	int32					Index = 0;
	FLinearColor			PartColor;

	MeshPart = GetPartInformation(InPart, ParamterName, Index);
	if (nullptr == MeshPart)
	{
		return PartColor;
	}

	UMaterialInstanceDynamic* materialDynamic = MeshPart->CreateDynamicMaterialInstance(Index);
	materialDynamic->GetVectorParameterValue(FName(*ParamterName), PartColor);

	return PartColor;
}

void ANetworkCharacter::SetSkeletalPartMesh(USkeletalMeshComponent* InMeshPart, int32 InMeshIndex)
{
	if (nullptr == InMeshPart)
	{
		return;
	}

	if (0 <= InMeshIndex || InMeshIndex < mCharacterAppearance.mMeshs.Num())
	{
		return;
	}

	//TEMP
	USkeletalMesh* NewMesh = nullptr; // = mSkeletalMeshs[InMeshIndex];
	if (nullptr == NewMesh)
	{
		return;
	}

	InMeshPart->SetSkeletalMesh(NewMesh);
}

void ANetworkCharacter::ConstructCharacter()
{
	USkeletalMeshComponent* meshRoot = GetMesh();
	int32 maxChild = meshRoot->GetNumChildrenComponents() + 1;
	mCharacterAppearance.mMeshs.Init(0, maxChild);

	for (int32 indexNumber = 0; indexNumber < maxChild; ++indexNumber)
	{

		USkeletalMeshComponent* partMesh = nullptr;
		if (indexNumber == 0)
		{
			partMesh = meshRoot;
		}
		else
		{
			partMesh = StaticCast<USkeletalMeshComponent*>(meshRoot->GetChildComponent(indexNumber - 1));
		}

		int32 itemCode = 0;
		if (partMesh->SkeletalMesh)
		{
			FString outMeshName = partMesh->SkeletalMesh->GetName();

			int32 findIndex = 0;
			outMeshName.FindLastChar('_', findIndex);
			if (findIndex != INDEX_NONE)
			{
				outMeshName.RemoveAt(0, findIndex + 1);
				itemCode = UNetworkUtils::ConvertStringToInt(outMeshName);
			}

		}

		mCharacterAppearance.mMeshs[indexNumber] = itemCode;
	}
}

