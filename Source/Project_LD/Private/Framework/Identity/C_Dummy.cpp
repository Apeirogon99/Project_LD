// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Identity/C_Dummy.h"

#include <Components/SkeletalMeshComponent.h>
#include <Components/StaticMeshComponent.h>

#include <Kismet/KismetMaterialLibrary.h>
#include <Network/NetworkUtils.h>

#include <Framework/Gameinstance/LDGameInstance.h>
#include <CharacterDatas.h>

AC_Dummy::AC_Dummy()
{
	PrimaryActorTick.bCanEverTick = false;

	mBodyMesh		= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mBodyMesh"));

	mHairMesh		= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mHairMesh"));
	mEyeMesh		= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mEyeMesh"));
	mEyebrowMesh	= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mEyebrowMesh"));


	USkeletalMeshComponent* meshRoot = GetMesh();
	if (meshRoot)
	{
		mBodyMesh->SetupAttachment(meshRoot);
		mHairMesh->SetupAttachment(meshRoot);
		mEyeMesh->SetupAttachment(meshRoot);
		mEyebrowMesh->SetupAttachment(meshRoot);
	}

}

void AC_Dummy::BeginPlay()
{
	Super::BeginPlay();
	
	SetTrib(ETribe::Man);
}

void AC_Dummy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_Dummy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AC_Dummy::SetStaticPartColor(UStaticMeshComponent* inPartMesh, const FString& inParameterName, FLinearColor inColor, int32 inIndex)
{
	UMaterialInstanceDynamic* materialDynamic =  inPartMesh->CreateDynamicMaterialInstance(inIndex);
	materialDynamic->SetVectorParameterValue(FName(*inParameterName), inColor);
}

void AC_Dummy::SetSkeletalPartColor(USkeletalMeshComponent* inPartMesh, const FString& inParameterName, FLinearColor inColor, int32 inIndex)
{
	UMaterialInstanceDynamic* materialDynamic = inPartMesh->CreateDynamicMaterialInstance(inIndex);
	materialDynamic->SetVectorParameterValue(FName(*inParameterName), inColor);
}

FLinearColor AC_Dummy::GetStaticPartColor(UStaticMeshComponent* inPartMesh, const FString& inParameterName, int32 inIndex)
{
	FLinearColor outColor;
	UMaterialInstanceDynamic* materialDynamic = inPartMesh->CreateDynamicMaterialInstance(inIndex);
	materialDynamic->GetVectorParameterValue(FName(*inParameterName), outColor);
	return outColor;
}

FLinearColor AC_Dummy::GetSkeletalPartColor(USkeletalMeshComponent* inPartMesh, const FString& inParameterName, int32 inIndex)
{
	FLinearColor outColor;
	UMaterialInstanceDynamic* materialDynamic = inPartMesh->CreateDynamicMaterialInstance(inIndex);
	materialDynamic->GetVectorParameterValue(FName(*inParameterName), outColor);
	return outColor;
}

void AC_Dummy::SetTrib(ETribe inTrib)
{
	mTribe = inTrib;
	switch (inTrib)
	{
	case ETribe::None:
		break;
	case ETribe::Man:
		mBodyMesh->SetSkeletalMesh(mManBodys[0]);
		mHairMesh->SetStaticMesh(mManHair[0]);
		mEyeMesh->SetStaticMesh(mManEye[0]);
		mEyebrowMesh->SetStaticMesh(mManEyebrow[0]);
		break;
	case ETribe::Woman:
		mBodyMesh->SetSkeletalMesh(mWomanBodys[0]);
		mHairMesh->SetStaticMesh(mWomanHair[0]);
		mEyeMesh->SetStaticMesh(mWomanEye[0]);
		mEyebrowMesh->SetStaticMesh(mWomanEyebrow[0]);
		break;
	case ETribe::Orc:
		mBodyMesh->SetSkeletalMesh(mOrcBodys[0]);
		mHairMesh->SetStaticMesh(mOrcHair[0]);
		mEyeMesh->SetStaticMesh(mOrcEye[0]);
		mEyebrowMesh->SetStaticMesh(mOrcEyebrow[0]);
		break;
	default:
		break;
	}
}

void AC_Dummy::SetClass(EClass inClass)
{
	mClass = inClass;
}

void AC_Dummy::SetPartColor(EPart inPart, FLinearColor inColor, int32 inIndex)
{
	UStaticMeshComponent* staticPart = nullptr;
	USkeletalMeshComponent* skeletalPart = nullptr;
	FString paramterName;
	switch (inPart)
	{
	case EPart::Body:
		paramterName = TEXT("BodyColor");
		skeletalPart = mBodyMesh;
		break;
	case EPart::Hair:
		paramterName = TEXT("HairColor");
		staticPart = mHairMesh;
		break;
	case EPart::Eye:
		paramterName = TEXT("EyeColor");
		staticPart = mEyeMesh;
		break;
	case EPart::Eyebrow:
		paramterName = TEXT("EyebrowColor");
		staticPart = mEyebrowMesh;
		break;
	default:
		break;
	}

	if (staticPart)
	{
		SetStaticPartColor(staticPart, paramterName, inColor, inIndex);
	}
	else if(skeletalPart)
	{
		SetSkeletalPartColor(skeletalPart, paramterName, inColor, inIndex);
	}

}

void AC_Dummy::SetCharacterDatas(const FCharacterDatas& inCharacterDatas)
{
	mCharacterDatas = inCharacterDatas;

	SetTrib(StaticCast<ETribe>(mCharacterDatas.mTribe));

	SetClass(StaticCast<EClass>(mCharacterDatas.mClass));

	SetPartColor(EPart::Body,		UNetworkUtils::ConverLinearColor(mCharacterDatas.mSkin));
	SetPartColor(EPart::Hair,		UNetworkUtils::ConverLinearColor(mCharacterDatas.mHair));
	SetPartColor(EPart::Eye,		UNetworkUtils::ConverLinearColor(mCharacterDatas.mEye));
	SetPartColor(EPart::Eyebrow,	UNetworkUtils::ConverLinearColor(mCharacterDatas.mEyebrow));
}

void AC_Dummy::SetAnimation(UAnimationAsset* inAnimationAsset)
{
	mBodyMesh->SetAnimationMode(EAnimationMode::AnimationSingleNode);
	mBodyMesh->SetAnimation(inAnimationAsset);
}

EClass AC_Dummy::GetClass()
{
	return mClass;
}

ETribe AC_Dummy::GetTribe()
{
	return mTribe;
}

FLinearColor AC_Dummy::GetPartColor(EPart inPart, int32 inIndex)
{
	UStaticMeshComponent* staticPart = nullptr;
	USkeletalMeshComponent* skeletalPart = nullptr;
	FString paramterName;
	switch (inPart)
	{
	case EPart::Body:
		paramterName = TEXT("BodyColor");
		skeletalPart = mBodyMesh;
		break;
	case EPart::Hair:
		paramterName = TEXT("HairColor");
		staticPart = mHairMesh;
		break;
	case EPart::Eye:
		paramterName = TEXT("EyeColor");
		staticPart = mEyeMesh;
		break;
	case EPart::Eyebrow:
		paramterName = TEXT("EyebrowColor");
		staticPart = mEyebrowMesh;
		break;
	default:
		break;
	}

	if (staticPart)
	{
		return GetStaticPartColor(staticPart, paramterName, inIndex);
	}
	else if (skeletalPart)
	{
		return GetSkeletalPartColor(skeletalPart, paramterName, inIndex);
	}

	return FLinearColor();
}

uint32 AC_Dummy::GetPartColorToInt(EPart inPart, int32 inIndex)
{
	FLinearColor color = GetPartColor(inPart, inIndex);
	uint32 colorInt = UNetworkUtils::ConverLinerColorToInt(color);
	return colorInt;
}
