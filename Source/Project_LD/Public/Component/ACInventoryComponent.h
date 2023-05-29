// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Struct/Game/GameDatas.h>
#include <Struct/Inventory/InventoryFrame.h>
#include "ACInventoryComponent.generated.h"


DECLARE_DELEGATE(FOnInventoryChanged);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_LD_API UACInventoryComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this component's properties
	UACInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Constants") int mColums;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Constants") int mRows;
	
	FOnInventoryChanged OnInventoryChanged;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UItemObjectData*> mInventoryData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UItemObjectData*> mInventoryObjectArr;

public:
	void																	Refresh();
	void																	ChangeInvenObjectArr();
	void																	LoadItem(int64 ObjectID, int32 ItemCode, int32 Pos_x, int32 Pos_y, int32 Rotation);
	void																	ClearInventory();
	void																	RemoveItem(UItemObjectData* ItemObjectData);
	void																	AddItemAt(UItemObjectData* ItemObjectData, int TopLeftIndex);
	bool																	TryAddItem(UItemObjectData* ItemObjectData);
	bool																	IsRoomAvailable(UItemObjectData* ItemObjectData, int TopLeftIndex);
	bool																	GetItemAtIndex(int index, UItemObjectData*& ItemObject);
	int																	TileToIndex(FTile Tile)	const;
	FTile																IndexToTile(int Index)		const;
	TArray<UItemObjectData*>							GetAllItems();
};
