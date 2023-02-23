// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Gameinstance/LDGameInstance.h"
#include <Engine/StreamableManager.h>

ULDGameInstance::ULDGameInstance()
{
}

ULDGameInstance::~ULDGameInstance()
{
}

void ULDGameInstance::Init()
{
	Super::Init();

	//FStreamableManager& StreamableManager = mAssetManager.GetStreamableManager();

	//TArray<FName> names;
	//FPrimaryAssetId itemAssetsId = FPrimaryAssetId(FPrimaryAssetType(FName("SkeletalMeshItems")), FName("SkeletalMeshItems"));

	//mAssetManager.LoadPrimaryAsset(itemAssetsId, names, FStreamableDelegate::CreateUObject(this, &ULDGameInstance::OnCompleteItemAssetsLoad));
}

void ULDGameInstance::OnCompleteItemAssetsLoad()
{
	//FStreamableManager& StreamableManager = mAssetManager.GetStreamableManager();
	//FPrimaryAssetId itemAssetsId = FPrimaryAssetId(FPrimaryAssetType(FName("SkeletalMeshItems")), FName("SkeletalMeshItems"));
	//FStringAssetReference referencePath = mAssetManager.GetPrimaryAssetPath(itemAssetsId);
	//StreamableManager.Unload(referencePath);
}
