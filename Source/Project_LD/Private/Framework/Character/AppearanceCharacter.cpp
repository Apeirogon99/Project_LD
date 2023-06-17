// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Character/AppearanceCharacter.h"
#include <Network/NetworkUtils.h>

#include <Framework/Game/PS_Game.h>
#include <Framework/Gameinstance/LDGameInstance.h>

#include <Struct/Game/GameDatas.h>

AAppearanceCharacter::AAppearanceCharacter()
{
	//Equipment
	mHelmet			= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mHelmet"));
	mHair			= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mHair"));
	mShoulders		= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mShoulders"));
	mChest			= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mChestAdd"));
	mBracers		= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mBracersAdd"));
	mHands			= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mHandsAdd"));
	mPants			= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mPantsAdd"));
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
		//EEquipment�ϰ� ���� ���� �ؾ��� (None���� ���ؼ� -1�� �ؾ���)
		//Appearance & Equipment
		mHair->SetupAttachment(meshRoot);
		mHelmet->SetupAttachment(meshRoot);
		mShoulders->SetupAttachment(meshRoot);
		mChest->SetupAttachment(meshRoot);
		mBracers->SetupAttachment(meshRoot);
		mHands->SetupAttachment(meshRoot);
		mPants->SetupAttachment(meshRoot);
		mBoots->SetupAttachment(meshRoot);

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

	//mCharacterPoses.Reserve(StaticCast<int32>(ECharacterPose::None));
}

AAppearanceCharacter::~AAppearanceCharacter()
{
}

void AAppearanceCharacter::InitializeAppearance()
{
	UpdateCharacterEquipment(mCharacterData.mEquipment);
	UpdateCharacterAppearnce(mCharacterData.mAppearance);
}

void AAppearanceCharacter::UpdateCharacterEquipment(const FCharacterEquipment& InCharacterEquipment)
{
	ECharacterRace currentRace = mCharacterData.mAppearance.mRace;
	if (currentRace == ECharacterRace::None)
	{
		UNetworkUtils::NetworkConsoleLog(TEXT("[ANetworkCharacter::GetPartInformation] Tribe is None"), ELogLevel::Error);
		return;
	}

	if (InCharacterEquipment.mHelmet == 0)
	{
		SetSkeletalPartMesh(mHair, InCharacterEquipment.mHair);
	}
	else
	{
		SetSkeletalPartMesh(mHelmet, InCharacterEquipment.mHelmet);
	}
	SetSkeletalPartMesh(mShoulders, InCharacterEquipment.mShoulders);
	SetSkeletalPartMesh(mChest,		InCharacterEquipment.mChest);
	SetSkeletalPartMesh(mBracers,	InCharacterEquipment.mBracers);
	SetSkeletalPartMesh(mHands,		InCharacterEquipment.mHands);

	if (InCharacterEquipment.mPants == 0)
	{
		switch (currentRace)
		{
		case ECharacterRace::Male:
			SetSkeletalPartMesh(mPants, 1);
			break;
		case ECharacterRace::Female:
			SetSkeletalPartMesh(mPants, 11);
			break;
		default:
			break;
		}
	}
	else
	{
		SetSkeletalPartMesh(mPants, InCharacterEquipment.mPants);
	}

	SetSkeletalPartMesh(mBoots,		InCharacterEquipment.mBoots);
	SetSkeletalPartMesh(mWeapon_L,	InCharacterEquipment.mWeapon_L);
	SetSkeletalPartMesh(mWeapon_R,	InCharacterEquipment.mWeapon_R);

	mCharacterData.mEquipment = InCharacterEquipment;
}

void AAppearanceCharacter::UpdateCharacterAppearnce(const FCharacterAppearance& InCharacterAppearance)
{
	ECharacterRace currentRace = mCharacterData.mAppearance.mRace;
	if (currentRace == ECharacterRace::None)
	{
		UNetworkUtils::NetworkConsoleLog(TEXT("[ANetworkCharacter::GetPartInformation] Tribe is None"), ELogLevel::Error);
		return;
	}

	uint32 skinColor	= StaticCast<uint32>(InCharacterAppearance.mSkin_Color);
	uint32 hairColor	= StaticCast<uint32>(InCharacterAppearance.mHair_Color);
	uint32 eyeColor		= StaticCast<uint32>(InCharacterAppearance.mEye_Color);
	uint32 eyebrowColor = StaticCast<uint32>(InCharacterAppearance.mEyebrow_Color);

	if (currentRace == ECharacterRace::Female)
	{
		SetSkeletalPartColor(GetMesh(), TEXT("BaseColor"), 0, skinColor);		//�ٵ�
		SetSkeletalPartColor(GetMesh(), TEXT("BaseColor"), 1, eyebrowColor);	//����
		SetSkeletalPartColor(GetMesh(), TEXT("BaseColor"), 2, eyeColor);		//��
		SetSkeletalPartColor(GetMesh(), TEXT("BaseColor"), 3, skinColor);		//�Ӹ�
		SetSkeletalPartColor(mHair,		TEXT("BaseColor"), 0, hairColor);		//���
	}
	else if(currentRace == ECharacterRace::Male || currentRace == ECharacterRace::Orc)
	{
		SetSkeletalPartColor(GetMesh(), TEXT("BaseColor"), 0, skinColor);		//�ٵ�
		SetSkeletalPartColor(GetMesh(), TEXT("BaseColor"), 1, skinColor);		//�Ӹ�
		SetSkeletalPartColor(GetMesh(), TEXT("BaseColor"), 2, eyeColor);		//��
		SetSkeletalPartColor(mHair,		TEXT("BaseColor"), 0, hairColor);		//���
	}

	mCharacterData.mAppearance = InCharacterAppearance;

}

void AAppearanceCharacter::UpdateCharacterPose(const ECharacterPose InCharacterPose)
{
	
	if (ECharacterPose::None == InCharacterPose)
	{
		return;
	}

	UAnimationAsset* animationAsset = mCharacterPoses[StaticCast<int32>(InCharacterPose)];
	if (animationAsset == nullptr)
	{
		return;
	}

	USkeletalMeshComponent* meshRoot = GetMesh();
	meshRoot->SetAnimationMode(EAnimationMode::AnimationSingleNode);
	meshRoot->SetAnimation(animationAsset);
	meshRoot->PlayAnimation(animationAsset, false);

	int32 maxChild = meshRoot->GetNumChildrenComponents();
	for (int32 indexNumber = 0; indexNumber < maxChild; ++indexNumber)
	{
		USkeletalMeshComponent* partMesh = StaticCast<USkeletalMeshComponent*>(meshRoot->GetChildComponent(indexNumber));
		if (partMesh)
		{
			partMesh->SetAnimationMode(EAnimationMode::AnimationSingleNode);
			partMesh->SetAnimation(animationAsset);
			partMesh->PlayAnimation(animationAsset, false);
		}
	}
}

void AAppearanceCharacter::UpdateDefaultAnimation()
{
	if (mDefaultAnimation == nullptr)
	{
		return;
	}

	USkeletalMeshComponent* meshRoot = GetMesh();
	meshRoot->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	meshRoot->SetAnimInstanceClass(mDefaultAnimation->GetClass());
	//meshRoot->PlayAnimation(mDefaultAnimation, false);

	int32 maxChild = meshRoot->GetNumChildrenComponents();
	for (int32 indexNumber = 0; indexNumber < maxChild; ++indexNumber)
	{
		USkeletalMeshComponent* partMesh = StaticCast<USkeletalMeshComponent*>(meshRoot->GetChildComponent(indexNumber));
		if (partMesh)
		{
			partMesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
			meshRoot->SetAnimInstanceClass(mDefaultAnimation->GetClass());
			//partMesh->PlayAnimation(mDefaultAnimation, false);
		}
	}
}

void AAppearanceCharacter::SetSkeletalPartColor(USkeletalMeshComponent* inMesh, const FString& inParamterName, int32 inIndex, uint32 inColor)
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
	else
	{
		UNetworkUtils::NetworkConsoleLog(TEXT("[ANetworkCharacter::SetSkeletalPartColor] MaterialDynamic is None"), ELogLevel::Error);
	}
}

void AAppearanceCharacter::SetSkeletalPartMesh(USkeletalMeshComponent* InMeshPart, int32 InMeshIndex)
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

	USkeletalMesh* NewMesh = itemData->mesh;
	if (nullptr == NewMesh)
	{
		return;
	}

	InMeshPart->SetSkeletalMesh(NewMesh);
}

void AAppearanceCharacter::SetSkeletalPartMesh(const ECharacterPart& inCharacterPart, const int32 inGameDataID)
{
	switch (inCharacterPart)
	{
	case ECharacterPart::None:
		break;
	case ECharacterPart::Helmet:
		SetSkeletalPartMesh(mHelmet, inGameDataID);
		break;
	case ECharacterPart::Shoulders:
		SetSkeletalPartMesh(mShoulders, inGameDataID);
		break;
	case ECharacterPart::Chest:
		SetSkeletalPartMesh(mChest, inGameDataID);
		break;
	case ECharacterPart::Bracers:
		SetSkeletalPartMesh(mBracers, inGameDataID);
		break;
	case ECharacterPart::Hands:
		SetSkeletalPartMesh(mHands, inGameDataID);
		break;
	case ECharacterPart::Pants:
		SetSkeletalPartMesh(mPants, inGameDataID);
		break;
	case ECharacterPart::Boots:
		SetSkeletalPartMesh(mBoots, inGameDataID);
		break;
	case ECharacterPart::Weapon_L:
		SetSkeletalPartMesh(mWeapon_L, inGameDataID);
		break;
	case ECharacterPart::Weapon_R:
		SetSkeletalPartMesh(mWeapon_R, inGameDataID);
		break;
	default:
		break;
	}
}

FLinearColor AAppearanceCharacter::GetMeshColor(const EAppearance InAppearance)
{
	USkeletalMeshComponent* mesh;
	int32					index;
	FLinearColor			meshColor;
	FString					paramterName = TEXT("BaseColor");

	ECharacterRace currentRace = mCharacterData.mAppearance.mRace;
	if (currentRace == ECharacterRace::None)
	{
		UNetworkUtils::NetworkConsoleLog(TEXT("[ANetworkCharacter::GetMeshColor] Race is None"), ELogLevel::Error);
		return FLinearColor();
	}

	switch (InAppearance)
	{
	case EAppearance::None:
		return FLinearColor();
		break;
	case EAppearance::Body:
		mesh = GetMesh();
		index = (currentRace == ECharacterRace::Female ? 0 : 0);
		break;
	case EAppearance::Eye:
		mesh = GetMesh();
		index = (currentRace == ECharacterRace::Female ? 2 : 2);
		break;
	case EAppearance::Eyebrow:
		mesh = GetMesh();
		index = (currentRace == ECharacterRace::Female ? 1 : 2);
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
		UNetworkUtils::NetworkConsoleLog(TEXT("[ANetworkCharacter::GetMeshColor] MaterialDynamic is None"), ELogLevel::Error);
		return FLinearColor();
	}
	materialDynamic->GetVectorParameterValue(FName(*paramterName), meshColor);

	meshColor.A = 1.0f;
	return meshColor;
}
