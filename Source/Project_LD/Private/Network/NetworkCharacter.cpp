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

void ANetworkCharacter::InitializeCharacterData(const FCharacterDatas& InCharacterDatas, const FCharacterAppearance& InCharacterAppearance)
{
	UpdateCharacterData(InCharacterDatas);
	UpdateCharacterAppearnce(InCharacterAppearance);
}

void ANetworkCharacter::UpdateCharacterData(const FCharacterDatas& InCharacterDatas)
{
	mCharacterData = InCharacterDatas;
}

void ANetworkCharacter::UpdateCharacterAppearnce(const FCharacterAppearance& InCharacterAppearance)
{	
	SetSkeletalPartColor(EPart::Body,		InCharacterAppearance.mBodyColor);
	SetSkeletalPartColor(EPart::Head,		InCharacterAppearance.mBodyColor);
	SetSkeletalPartColor(EPart::Eye,		InCharacterAppearance.mEyeColor);
	SetSkeletalPartColor(EPart::Eyebrow,	InCharacterAppearance.mEyeColor);
	SetSkeletalPartColor(EPart::Hair,		InCharacterAppearance.mHairColor);

	USkeletalMeshComponent* meshRoot = GetMesh();
	int32 maxChild = meshRoot->GetNumChildrenComponents();
	for (int32 indexNumber = 0; indexNumber < maxChild; ++indexNumber)
	{
		int32 oldMesh = mCharacterAppearance.mMeshs[indexNumber];
		int32 newMesh = InCharacterAppearance.mMeshs[indexNumber];
		if (oldMesh != newMesh)
		{
			USkeletalMeshComponent* partMesh = StaticCast<USkeletalMeshComponent*>(meshRoot->GetChildComponent(indexNumber));
			SetSkeletalPartMesh(partMesh, newMesh);
		}
	}

	mCharacterAppearance = InCharacterAppearance;

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

bool ANetworkCharacter::GetPartInformation(const EPart InPart, USkeletalMeshComponent* outMeshPart, FString OutParamterName, int32 OutIndex)
{
	USkeletalMeshComponent* MeshPart = nullptr;
	FString					ParamterName = TEXT("");
	int32					Index = 0;

	if (InPart == EPart::None)
	{
		UNetworkUtils::NetworkConsoleLog(TEXT("[ANetworkCharacter::GetPartInformation] Part is None"), ELogLevel::Error);
		return false;	
	}

	ETribe currentTribe = StaticCast<ETribe>(mCharacterData.mTribe);
	if (currentTribe == ETribe::None)
	{
		UNetworkUtils::NetworkConsoleLog(TEXT("[ANetworkCharacter::GetPartInformation] Tribe is None"), ELogLevel::Error);
	}

	switch (InPart)
	{
	case EPart::Body:
		MeshPart = GetMesh();
		ParamterName = TEXT("BaseColor");
		Index = 0;
		break;
	case EPart::Head:
		MeshPart = GetMesh();
		ParamterName = TEXT("BaseColor");
		Index = (currentTribe == ETribe::Woman ? 3 : 1);
		break;
	case EPart::Eye:
		MeshPart = GetMesh();
		ParamterName = TEXT("BaseColor");
		Index = (currentTribe == ETribe::Woman ? 1 : 2);
		break;
	case EPart::Eyebrow:
		MeshPart = GetMesh();
		ParamterName = TEXT("BaseColor");
		Index = (currentTribe == ETribe::Woman ? 2 : 2);
		break;
	case EPart::Hair:
		MeshPart = mHair;
		ParamterName = TEXT("BaseColor");
		Index = 2;
		break;
	default:
		break;
	}

	if (nullptr == MeshPart)
	{
		return false;
	}

	outMeshPart = MeshPart;
	OutParamterName = ParamterName;
	OutIndex = Index;

	return true;
}

void ANetworkCharacter::SetSkeletalPartColor(const EPart InPart, uint32 InColor)
{
	USkeletalMeshComponent* MeshPart = nullptr;
	FString					ParamterName = TEXT("");
	int32					Index = 0;

	FLinearColor partColor = UNetworkUtils::ConverLinearColor(InColor);
	if (GetStaticPartColor(InPart) == partColor)
	{
		return;
	}

	GetPartInformation(InPart, MeshPart, ParamterName, Index);

	UMaterialInstanceDynamic* materialDynamic = MeshPart->CreateDynamicMaterialInstance(Index);
	materialDynamic->SetVectorParameterValue(FName(*ParamterName), partColor);
}

FLinearColor ANetworkCharacter::GetStaticPartColor(const EPart InPart)
{
	USkeletalMeshComponent* MeshPart = nullptr;
	FString					ParamterName = TEXT("");
	int32					Index = 0;
	FLinearColor			PartColor;

	GetPartInformation(InPart, MeshPart, ParamterName, Index);

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

	if (0 < InMeshIndex || InMeshIndex < mSkeletalMeshs.Num())
	{
		return;
	}

	//TEMP
	USkeletalMesh* NewMesh = mSkeletalMeshs[InMeshIndex];
	if (nullptr == NewMesh)
	{
		return;
	}

	InMeshPart->SetSkeletalMesh(NewMesh);
}

