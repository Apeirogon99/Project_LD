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
		//EEquipment하고 순서 같게 해야함 (None으로 인해서 -1은 해야함)
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

void AAppearanceCharacter::InitCharacterVisual(const FCharacterAppearance& InCharacterAppearance, const FCharacterEquipment& inCharacterEquipment)
{
	mCharacterAppearance = InCharacterAppearance;
	mCharacterEquipment = inCharacterEquipment;
}

void AAppearanceCharacter::InitCharacterAnimation()
{
	if (mCharacterAppearance.GetRace() == ECharacterRace::Male)
	{
		mAnimationInstance = LoadClass<UAnimInstance>(nullptr, TEXT("AnimBlueprint'/Game/GameContent/Animation/Male/BP_Anim_Hu_M.BP_Anim_Hu_M_C'"));
	}
	else if (mCharacterAppearance.GetRace() == ECharacterRace::Female)
	{
		//mAnimationInstance = LoadClass;
	}

	UpdateDefaultAnimation();
}

void AAppearanceCharacter::UpdateCharacterVisual(const FCharacterAppearance& InCharacterAppearance, const FCharacterEquipment& inCharacterEquipment)
{
	mCharacterAppearance = InCharacterAppearance;
	mCharacterEquipment = inCharacterEquipment;

	UpdateCharacterEquipment(inCharacterEquipment);
	UpdateCharacterAppearnce(InCharacterAppearance);
}

void AAppearanceCharacter::UpdateCharacterEquipment(const FCharacterEquipment& InCharacterEquipment)
{
	ECharacterRace currentRace = mCharacterAppearance.GetRace();
	if (currentRace == ECharacterRace::None)
	{
		UNetworkUtils::NetworkConsoleLog(TEXT("[ANetworkCharacter::UpdateCharacterEquipment] Tribe is None"), ELogLevel::Error);
		return;
	}

	if (InCharacterEquipment.GetHelmet() == 0)
	{
		SetSkeletalPartMesh(mHair, InCharacterEquipment.GetHair());
	}

	SetSkeletalPartMesh(mHelmet,	InCharacterEquipment.GetHelmet());
	SetSkeletalPartMesh(mShoulders, InCharacterEquipment.GetShoulders());
	SetSkeletalPartMesh(mChest,		InCharacterEquipment.GetChest());
	SetSkeletalPartMesh(mBracers,	InCharacterEquipment.GetBracers());
	SetSkeletalPartMesh(mHands,		InCharacterEquipment.GetHands());

	if (InCharacterEquipment.GetPants() == 0)
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
		SetSkeletalPartMesh(mPants, InCharacterEquipment.GetPants());
	}

	SetSkeletalPartMesh(mBoots,		InCharacterEquipment.GetBoots());
	SetSkeletalPartMesh(mWeapon_L,	InCharacterEquipment.GetWeaponL());
	SetSkeletalPartMesh(mWeapon_R,	InCharacterEquipment.GetWeaponR());

	mCharacterEquipment = InCharacterEquipment;
}

void AAppearanceCharacter::UpdateCharacterAppearnce(const FCharacterAppearance& InCharacterAppearance)
{
	ECharacterRace currentRace = mCharacterAppearance.GetRace();
	if (currentRace == ECharacterRace::None)
	{
		UNetworkUtils::NetworkConsoleLog(TEXT("[ANetworkCharacter::UpdateCharacterAppearnce] Tribe is None"), ELogLevel::Error);
		return;
	}

	uint32 skinColor	= StaticCast<uint32>(InCharacterAppearance.GetSkinColor());
	uint32 hairColor	= StaticCast<uint32>(InCharacterAppearance.GetHairColor());
	uint32 eyeColor		= StaticCast<uint32>(InCharacterAppearance.GetEyeColor());
	uint32 eyebrowColor = StaticCast<uint32>(InCharacterAppearance.GetEyebrowColor());

	if (currentRace == ECharacterRace::Female)
	{
		SetSkeletalPartColor(GetMesh(), TEXT("BaseColor"), 0, skinColor);		//바디
		SetSkeletalPartColor(GetMesh(), TEXT("BaseColor"), 1, eyebrowColor);	//눈썹
		SetSkeletalPartColor(GetMesh(), TEXT("BaseColor"), 2, eyeColor);		//눈
		SetSkeletalPartColor(GetMesh(), TEXT("BaseColor"), 3, skinColor);		//머리
		SetSkeletalPartColor(mHair,		TEXT("BaseColor"), 0, hairColor);		//헤어
	}
	else if(currentRace == ECharacterRace::Male || currentRace == ECharacterRace::Orc)
	{
		SetSkeletalPartColor(GetMesh(), TEXT("BaseColor"), 0, skinColor);		//바디
		SetSkeletalPartColor(GetMesh(), TEXT("BaseColor"), 1, skinColor);		//머리
		SetSkeletalPartColor(GetMesh(), TEXT("BaseColor"), 2, eyeColor);		//눈
		SetSkeletalPartColor(mHair,		TEXT("BaseColor"), 0, hairColor);		//헤어
	}

	mCharacterAppearance = InCharacterAppearance;

}

void AAppearanceCharacter::UpdateCharacterPose(const ECharacterPose InCharacterPose)
{
	if (mCharacterPoses.Num() == 0)
	{
		return;
	}

	UAnimationAsset* animationAsset = mCharacterPoses[StaticCast<int32>(InCharacterPose)];
	if (animationAsset == nullptr)
	{
		return;
	}

	bool isLoop = false;
	if (ECharacterPose::Default == InCharacterPose || ECharacterPose::Idle == InCharacterPose)
	{
		isLoop = true;
	}

	USkeletalMeshComponent* meshRoot = GetMesh();
	meshRoot->SetAnimationMode(EAnimationMode::AnimationSingleNode);
	meshRoot->SetAnimation(animationAsset);
	meshRoot->PlayAnimation(animationAsset, isLoop);

	int32 maxChild = meshRoot->GetNumChildrenComponents();
	for (int32 indexNumber = 0; indexNumber < maxChild; ++indexNumber)
	{
		USkeletalMeshComponent* partMesh = StaticCast<USkeletalMeshComponent*>(meshRoot->GetChildComponent(indexNumber));
		if (partMesh)
		{
			partMesh->SetAnimationMode(EAnimationMode::AnimationSingleNode);
			partMesh->SetAnimation(animationAsset);
			partMesh->PlayAnimation(animationAsset, isLoop);
		}
	}
}

void AAppearanceCharacter::UpdateCharacterMontage(UAnimMontage* inMontageToPlay, const float& inStartAtTime)
{
	USkeletalMeshComponent* meshRoot = GetMesh();
	meshRoot->GetAnimInstance()->Montage_Play(inMontageToPlay, 1.0f, EMontagePlayReturnType::MontageLength, inStartAtTime);

	int32 maxChild = meshRoot->GetNumChildrenComponents();
	UE_LOG(LogTemp, Warning, TEXT("UpdateCharacterMontage Child %d"), maxChild);
	for (int32 indexNumber = 0; indexNumber < maxChild; ++indexNumber)
	{
		USkeletalMeshComponent* partMesh = StaticCast<USkeletalMeshComponent*>(meshRoot->GetChildComponent(indexNumber));
		if (partMesh->GetAnimInstance())
		{
			partMesh->GetAnimInstance()->Montage_Play(inMontageToPlay, 1.0f, EMontagePlayReturnType::MontageLength, inStartAtTime);
		}
	}
}

void AAppearanceCharacter::UpdateDefaultAnimation()
{
	/*
	if (mCharacterPoses.Num() == 0)
	{
		return;
	}*/

	if (mAnimationInstance == nullptr)
	{
		return;
	}

	USkeletalMeshComponent* meshRoot = GetMesh();
	meshRoot->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	meshRoot->SetAnimClass(mAnimationInstance);

	int32 maxChild = meshRoot->GetNumChildrenComponents();
	for (int32 indexNumber = 0; indexNumber < maxChild; ++indexNumber)
	{
		USkeletalMeshComponent* partMesh = StaticCast<USkeletalMeshComponent*>(meshRoot->GetChildComponent(indexNumber));
		if (partMesh)
		{
			partMesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
			partMesh->SetAnimClass(mAnimationInstance);
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

	if (-1 >= InMeshIndex)
	{
		return;
	}

	if (0 == InMeshIndex)
	{
		InMeshPart->SetSkeletalMesh(nullptr);
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

	USkeletalMesh* NewMesh = itemData->GetMesh();
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

	ECharacterRace currentRace = mCharacterAppearance.GetRace();
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