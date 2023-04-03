// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/NetworkCharacter.h"
#include <Network/NetworkUtils.h>
#include <Framework/Gameinstance/LDGameInstance.h>
#include <Struct/Game/GameDatas.h>

// Sets default values
ANetworkCharacter::ANetworkCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Appearance
	//GetMesh() == 머리
	mFacials		= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mFacials"));		//얼굴 장식 == 오크 해당
	mEars			= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mEars"));
	mChest			= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mChest"));
	mBracers		= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mBracers"));
	mHands			= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mHands"));
	mPants			= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mPants"));
	mLegs			= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mLegs"));
	mFeet			= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mFeet"));

	//Equipment
	mHelmet			= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mHelmet"));
	mHair			= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mHair"));
	mShoulders		= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mShoulders"));
	mChestAdd		= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mChestAdd"));
	mBracersAdd		= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mBracersAdd"));
	mHandsAdd		= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mHandsAdd"));
	mPantsAdd		= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mPantsAdd"));
	mBoots			= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mBoots"));

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
		//EEquipment하고 순서 같게 해야함 (None으로 인해서 -1은 해야함)
		//Appearance & Equipment
		//1. Head
		mHair->SetupAttachment(meshRoot);
		mFacials->SetupAttachment(meshRoot);
		mEars->SetupAttachment(meshRoot);
		mHelmet->SetupAttachment(meshRoot);

		mShoulders->SetupAttachment(meshRoot);
		mChest->SetupAttachment(meshRoot);
		mChestAdd->SetupAttachment(meshRoot);
		mBracers->SetupAttachment(meshRoot);
		mBracersAdd->SetupAttachment(meshRoot);
		mHands->SetupAttachment(meshRoot);
		mHandsAdd->SetupAttachment(meshRoot);

		mPants->SetupAttachment(meshRoot);
		mPantsAdd->SetupAttachment(meshRoot);
		mLegs->SetupAttachment(meshRoot);
		mBoots->SetupAttachment(meshRoot);
		mFeet->SetupAttachment(meshRoot);

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

void ANetworkCharacter::InitializeCharacter(const FCharacterAppearance& InCharacterAppearance, const FCharacterEquipment& InCharacterEquipment)
{
	mCharacterAppearance = InCharacterAppearance;
	mChracterEquipment = InCharacterEquipment;

	UpdateCharacterEquipment(InCharacterEquipment);
	UpdateCharacterAppearnce(InCharacterAppearance);
}

void ANetworkCharacter::UpdateCharacterAppearnce(const FCharacterAppearance& InCharacterAppearance)
{
	ERace currentRace = StaticCast<ERace>(InCharacterAppearance.mRace);
	if (currentRace == ERace::None)
	{
		UNetworkUtils::NetworkConsoleLog(TEXT("[ANetworkCharacter::GetPartInformation] Tribe is None"), ELogLevel::Error);
		return;
	}

	uint32 skinColor = StaticCast<uint32>(InCharacterAppearance.mSkin_Color);
	uint32 hairColor = StaticCast<uint32>(InCharacterAppearance.mHair_Color);
	uint32 eyeColor = StaticCast<uint32>(InCharacterAppearance.mEye_Color);
	uint32 eyebrowColor = StaticCast<uint32>(InCharacterAppearance.mEyebrow_Color);

	SetSkeletalPartColor(GetMesh(), TEXT("BaseColor"), (currentRace == ERace::Female ? 2 : 0), skinColor);		//머리
	SetSkeletalPartColor(mHair,		TEXT("BaseColor"), 0, hairColor);		//헤어
	SetSkeletalPartColor(mEars,		TEXT("BaseColor"), 0, skinColor);		//귀
	SetSkeletalPartColor(GetMesh(), TEXT("BaseColor"), (currentRace == ERace::Female ? 1 : 1), eyeColor);		//눈
	SetSkeletalPartColor(GetMesh(), TEXT("BaseColor"), (currentRace == ERace::Female ? 0 : 1), eyebrowColor);	//눈썹
	SetSkeletalPartColor(mBracers,	TEXT("BaseColor"), 0, skinColor);		//팔
	SetSkeletalPartColor(mChest,	TEXT("BaseColor"), 0, skinColor);		//가슴
	SetSkeletalPartColor(mHands,	TEXT("BaseColor"), 0, skinColor);		//손
	SetSkeletalPartColor(mPants,	TEXT("BaseColor"), 0, skinColor);		//하의
	SetSkeletalPartColor(mLegs,		TEXT("BaseColor"), 0, skinColor);		//다리
	SetSkeletalPartColor(mFeet,		TEXT("BaseColor"), 0, skinColor);		//발

	SetSkeletalPartColor(mChestAdd, TEXT("BaseColor"), (currentRace == ERace::Orc ? 1 : 0), skinColor);
	SetSkeletalPartColor(mBoots,	TEXT("BaseColor"), (currentRace == ERace::Orc ? 0 : 1), skinColor);

	mCharacterAppearance.mSkin_Color = InCharacterAppearance.mSkin_Color;
	mCharacterAppearance.mHair_Color = InCharacterAppearance.mHair_Color;
	mCharacterAppearance.mEye_Color = InCharacterAppearance.mEye_Color;
	mCharacterAppearance.mEyebrow_Color = InCharacterAppearance.mEyebrow_Color;
}

void ANetworkCharacter::UpdateCharacterEquipment(const FCharacterEquipment& InCharacterEquipment)
{

	//USkeletalMeshComponent* meshRoot = GetMesh();
	//int32 maxChild = meshRoot->GetNumChildrenComponents() + 1;

	

	//for (int32 indexNumber = 0; indexNumber < maxChild; ++indexNumber)
	//{
	//	int32 oldMesh = mCharacterAppearance.mMeshs[indexNumber];
	//	int32 newMesh = InCharacterAppearance.mMeshs[indexNumber];

	//	if (oldMesh != newMesh)
	//	{
	//		USkeletalMeshComponent* partMesh = nullptr;

	//		if (indexNumber == 0)
	//		{
	//			partMesh = meshRoot;
	//		}
	//		else
	//		{
	//			partMesh = StaticCast<USkeletalMeshComponent*>(meshRoot->GetChildComponent(indexNumber - 1));
	//		}

	//		SetSkeletalPartMesh(partMesh, newMesh);

	//	}

	//	mCharacterAppearance.mMeshs[indexNumber] = InCharacterAppearance.mMeshs[indexNumber];
	//}

	ERace currentRace = StaticCast<ERace>(mCharacterAppearance.mRace);
	if (currentRace == ERace::None)
	{
		UNetworkUtils::NetworkConsoleLog(TEXT("[ANetworkCharacter::GetPartInformation] Tribe is None"), ELogLevel::Error);
		return;
	}

	SetSkeletalPartMesh(mHair,			InCharacterEquipment.mHair);
	SetSkeletalPartMesh(mHelmet,		InCharacterEquipment.mHelmet);
	SetSkeletalPartMesh(mShoulders,		InCharacterEquipment.mShoulders);
	SetSkeletalPartMesh(mChestAdd,		InCharacterEquipment.mChestAdd);
	SetSkeletalPartMesh(mBracersAdd,	InCharacterEquipment.mBracersAdd);
	SetSkeletalPartMesh(mHandsAdd,		InCharacterEquipment.mHandsAdd);

	if (InCharacterEquipment.mPantsAdd == 0)
	{
		switch (currentRace)
		{
		case ERace::Male:
			SetSkeletalPartMesh(mPantsAdd, 130);
			break;
		case ERace::Female:
			SetSkeletalPartMesh(mPantsAdd, 100);
			break;
		case ERace::Orc:
			SetSkeletalPartMesh(mPantsAdd, 160);
			break;
		default:
			break;
		}
	}
	else
	{
		SetSkeletalPartMesh(mPantsAdd, InCharacterEquipment.mPantsAdd);
	}
	SetSkeletalPartMesh(mBoots,			InCharacterEquipment.mBoots);

	SetSkeletalPartMesh(mWeapon_L,		InCharacterEquipment.mWeapon_L);
	SetSkeletalPartMesh(mWeapon_R,		InCharacterEquipment.mWeapon_R);

	mChracterEquipment = InCharacterEquipment;

	//SetSkeletalPartMesh(mEars,				InCharacterEquipment.mEars);
	//SetSkeletalPartMesh(mFacials_01,		InCharacterEquipment.mFacials_01);
	//SetSkeletalPartMesh(mSkirt,				InCharacterEquipment.mSkirt);
	//SetSkeletalPartMesh(mLegsAdd,			InCharacterEquipment.mLegsAdd);
	//SetSkeletalPartMesh(mCape,				InCharacterEquipment.mCape);
	//SetSkeletalPartMesh(mBracers,			InCharacterEquipment.mBracers);
	//SetSkeletalPartMesh(mBelt,				InCharacterEquipment.mBelt);
	//SetSkeletalPartMesh(mTabard,			InCharacterEquipment.mTabard);


	//SetSkeletalPartMesh(mBack_2HL,		InCharacterAppearance.mBack_2HL);
	//SetSkeletalPartMesh(mBack_Shield,		InCharacterAppearance.mBack_Shield);
	//SetSkeletalPartMesh(mBack_WeaponL,	InCharacterAppearance.mBack_WeaponL);
	//SetSkeletalPartMesh(mBack_WeaponR,	InCharacterAppearance.mBack_WeaponR);
	//SetSkeletalPartMesh(mBack_Bow,		InCharacterAppearance.mBack_Bow);
	//SetSkeletalPartMesh(mQuiver,			InCharacterAppearance.mQuiver);
	//SetSkeletalPartMesh(mWeapon_R_Arrow,	InCharacterAppearance.mWeapon_R_Arrow);
	//SetSkeletalPartMesh(mWeapon_Shield,	InCharacterAppearance.mWeapon_Shield);
	//SetSkeletalPartMesh(mHip_L,			InCharacterAppearance.mHip_L);
	//SetSkeletalPartMesh(mHip_R,			InCharacterAppearance.mHip_R);
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

FLinearColor ANetworkCharacter::GetMeshColor(const EAppearance InAppearance)
{
	USkeletalMeshComponent* mesh;
	int32					index;
	FLinearColor			meshColor;
	FString					paramterName = TEXT("BaseColor");

	ERace currentTribe = StaticCast<ERace>(mCharacterAppearance.mRace);
	if (currentTribe == ERace::None)
	{
		UNetworkUtils::NetworkConsoleLog(TEXT("[ANetworkCharacter::GetPartInformation] Tribe is None"), ELogLevel::Error);
		return FLinearColor();
	}

	switch (InAppearance)
	{
	case EAppearance::None:
		return FLinearColor();
		break;
	case EAppearance::Body:
		mesh = GetMesh();
		index = (currentTribe == ERace::Female ? 2 : 0);
		break;
	case EAppearance::Eye:
		mesh = GetMesh();
		index = (currentTribe == ERace::Female ? 1 : 1);
		break;
	case EAppearance::Eyebrow:
		mesh = GetMesh();
		index = (currentTribe == ERace::Female ? 0 : 1);
		break;
	case EAppearance::Hair:
		mesh = mHair;
		index = 0;
		break;
	default:
		return FLinearColor();
		break;
	}

	UMaterialInstanceDynamic* materialDynamic = mesh->CreateDynamicMaterialInstance(index);
	if (materialDynamic == nullptr)
	{
		return FLinearColor();
	}
	materialDynamic->GetVectorParameterValue(FName(*paramterName), meshColor);

	return meshColor;
}

void ANetworkCharacter::SetSkeletalPartColor(USkeletalMeshComponent* inMesh, const FString& inParamterName, int32 inIndex, uint32 inColor)
{
	USkeletalMeshComponent*			meshPart = inMesh;
	FString							paramterName = inParamterName;
	int32							index = inIndex;
	uint32							color = inColor;

	if (nullptr == meshPart->SkeletalMesh)
	{
		return;
	}

	FLinearColor meshColor = UNetworkUtils::ConverLinearColor(color);
	UMaterialInstanceDynamic* materialDynamic = meshPart->CreateDynamicMaterialInstance(index);
	if (materialDynamic)
	{
		materialDynamic->SetVectorParameterValue(FName(*paramterName), meshColor);
	}
}

void ANetworkCharacter::SetSkeletalPartMesh(USkeletalMeshComponent* InMeshPart, int32 InMeshIndex)
{
	if (nullptr == InMeshPart)
	{
		return;
	}

	if (0 >= InMeshIndex)
	{
		return;
	}

	ULDGameInstance* gameInstance = Cast<ULDGameInstance>(GetGameInstance());
	if (nullptr == gameInstance)
	{
		return;
	}

	FItemData* itemData = gameInstance->GetItemData(InMeshIndex);
	if (nullptr == itemData)
	{
		return;
	}

	//TEMP
	USkeletalMesh* NewMesh = itemData->mesh;
	if (nullptr == NewMesh)
	{
		return;
	}

	//UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("장착 : %s - %s"), *InMeshPart->GetFName().ToString(), *NewMesh->GetFName().ToString()), ELogLevel::Warning);
	InMeshPart->SetSkeletalMesh(NewMesh);
}

void ANetworkCharacter::ConstructCharacter()
{
	//USkeletalMeshComponent* meshRoot = GetMesh();
	//int32 maxChild = meshRoot->GetNumChildrenComponents() + 1;
	//mCharacterAppearance.mMeshs.Init(0, maxChild);

	//for (int32 indexNumber = 0; indexNumber < maxChild; ++indexNumber)
	//{

	//	USkeletalMeshComponent* partMesh = nullptr;
	//	if (indexNumber == 0)
	//	{
	//		partMesh = meshRoot;
	//	}
	//	else
	//	{
	//		partMesh = StaticCast<USkeletalMeshComponent*>(meshRoot->GetChildComponent(indexNumber - 1));
	//	}

	//	int32 itemCode = 0;
	//	if (partMesh->SkeletalMesh)
	//	{
	//		FString outMeshName = partMesh->SkeletalMesh->GetName();

	//		int32 findIndex = 0;
	//		outMeshName.FindLastChar('_', findIndex);
	//		if (findIndex != INDEX_NONE)
	//		{
	//			outMeshName.RemoveAt(0, findIndex + 1);
	//			itemCode = UNetworkUtils::ConvertStringToInt(outMeshName);
	//		}

	//	}

	//	mCharacterAppearance.mMeshs[indexNumber] = itemCode;
	//}
}

