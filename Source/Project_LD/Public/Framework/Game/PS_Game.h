// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Network/NetworkPlayerState.h"
#include <Struct/Game/GameDatas.h>
#include <Struct/Inventory/InventoryFrame.h>
#include "PS_Game.generated.h"

/**
 * 
 */
DECLARE_DELEGATE(FOnInventoryChanged);

UCLASS()
class PROJECT_LD_API APS_Game : public ANetworkPlayerState
{
	GENERATED_BODY()

public:
	APS_Game();
	~APS_Game();

	virtual void PostInitializeComponents() override;
	virtual void Destroyed() override;

	void Init();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UItemObjectData*> mInventoryData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UItemObjectData*> mInventoryObjectArr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detect")		bool mIsChange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Constants") int mColums;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Constants") int mRows;

	FOnInventoryChanged OnInventoryChanged;

public:
	UFUNCTION(BlueprintCallable)
	void																	RemoveItem(UItemObjectData* ItemObjectData);
	UFUNCTION(BlueprintCallable)
	void																	AddItemAt(UItemObjectData* ItemObjectData, int TopLeftIndex);
	UFUNCTION(BlueprintCallable)
	bool																	TryAddItem(UItemObjectData* ItemObjectData);
	UFUNCTION(BlueprintCallable)
	bool																	IsRoomAvailable(UItemObjectData* ItemObjectData, int TopLeftIndex);
	UFUNCTION(BlueprintCallable)
	int																	TileToIndex(FTile Tile)	const;
	UFUNCTION(BlueprintCallable)
	FTile																IndexToTile(int Index)		const;
	UFUNCTION(BlueprintCallable)
	TArray<UItemObjectData*>							GetAllItems();
	UFUNCTION(BlueprintCallable)
	bool																	GetItemAtIndex(int index, UItemObjectData*& ItemObject);
	void																	InventoryChangeDetected();

public:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "PlayerState | Attack", meta = (AllowPrivateAccess = "true"))
	float mAttackRange;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "PlayerState | Attack", meta = (AllowPrivateAccess = "true"))
	float mAttackRadius;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "PlayerState | Health", meta = (AllowPrivateAccess = "true"))
	float mMaxHealth;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "PlayerState | Health", meta = (AllowPrivateAccess = "true"))
	float mCurrentHealth;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "PlayerState | Mana", meta = (AllowPrivateAccess = "true"))
	float mMaxMana;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "PlayerState | Mana", meta = (AllowPrivateAccess = "true"))
	float mCurrentMana;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "PlayerState | Level", meta = (AllowPrivateAccess = "true"))
	int32 mCharacterLevel;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "PlayerState | Condition", meta = (AllowPrivateAccess = "true"))
	bool mIsAttacking;

public:
	void Init(const int64 inRemoteID);
	
public:
	int64 GetRemoteID();

public:
	int64 mRemoteID;
};
