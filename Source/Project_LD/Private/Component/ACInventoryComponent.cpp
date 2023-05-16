// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/ACInventoryComponent.h"


// Sets default values for this component's properties
UACInventoryComponent::UACInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Colums = 15;
	Rows = 6;

	IsChange = false;
}


// Called when the game starts
void UACInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	//ItemArr resize
	ItemDataArr.SetNum(Colums * Rows);
}

void UACInventoryComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	OnInventoryChanged.Clear();
}


// Called every frame
void UACInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsChange)
	{
		IsChange = false;
		if (OnInventoryChanged.IsBound() == true)
		{
			OnInventoryChanged.Broadcast();
		}
	}
}

void UACInventoryComponent::RemoveItem(FItemData& ItemObjectData)
{
	if (ItemObjectData.IsValid() == true)
	{
		int itemIndex = 0;
		for (FValidFirstItemData& itemData : ItemDataArr)
		{
			if (itemData.ItemObjectData == ItemObjectData)
			{
				ItemDataArr[itemIndex] = FValidFirstItemData();
				IsChange = true;
			}
			itemIndex++;
		}
	}
}

void UACInventoryComponent::AddItemAt(FItemData& ItemObjectData, int TopLeftIndex)
{
	FTile TileData = IndexToTile(TopLeftIndex);
	int X = ItemObjectData.size_x;
	int Y = ItemObjectData.size_y;
	for (int FIndex = TileData.X; FIndex < TileData.X + X; FIndex++)
	{
		for (int SIndex = TileData.Y; SIndex < TileData.Y + Y; SIndex++)
		{
			FTile LocalTile = FTile();
			LocalTile.X = FIndex;
			LocalTile.Y = SIndex;
			if ((FIndex == TileData.X) && (SIndex == TileData.Y))
			{
				ItemDataArr[TileToIndex(LocalTile)].first = true;
			}
			else
			{
				ItemDataArr[TileToIndex(LocalTile)].first = false;
			}
			ItemDataArr[TileToIndex(LocalTile)].ItemObjectData = ItemObjectData;
		}
	}
	IsChange = true;
}

bool UACInventoryComponent::TryAddItem(FItemData& ItemObjectData)
{
	if(ItemObjectData.IsValid() == true)
	{
		int itemIndex = 0;
		for (FValidFirstItemData& itemData : ItemDataArr)
		{
			if(IsRoomAvailable(ItemObjectData,itemIndex))
			{
				AddItemAt(ItemObjectData,itemIndex);
				return true;
			}
			itemIndex++;
		}
		int32 temp = ItemObjectData.size_x;
		ItemObjectData.rotation = 1;
		ItemObjectData.size_x = ItemObjectData.size_y;
		ItemObjectData.size_y = temp;
	
		itemIndex = 0;
		for (FValidFirstItemData& itemData : ItemDataArr)
		{
			if(IsRoomAvailable(ItemObjectData,itemIndex))
			{
				AddItemAt(ItemObjectData,itemIndex);
				return true;
			}		
			itemIndex++;
		}
		return false;
	}
	return false;
}

bool UACInventoryComponent::IsRoomAvailable(FItemData& ItemObjectData, int TopLeftIndex)
{
	FTile TileData = IndexToTile(TopLeftIndex);
	int X = ItemObjectData.size_x;
	int Y = ItemObjectData.size_y;

	for (int FIndex = TileData.X; FIndex < TileData.X + X; FIndex++)
	{
		for (int SIndex = TileData.Y; SIndex < TileData.Y + Y; SIndex++)
		{
			if ((FIndex >= 0) && (SIndex >= 0) && (FIndex < Colums) && (SIndex < Rows))
			{
				FTile LocalTile = FTile();
				LocalTile.X = FIndex;
				LocalTile.Y = SIndex;

				FReturnItemAtIndex Data = FReturnItemAtIndex();
				Data=GetItemAtIndex(TileToIndex(LocalTile));
				if (Data.valid)
				{
					if (Data.ItemObjectData.IsValid() == true)
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
	}
	return true;
}

int UACInventoryComponent::TileToIndex(FTile Tile) const
{
	return Tile.X + Tile.Y * Colums;
}

FTile UACInventoryComponent::IndexToTile(int Index) const
{
	FTile Node = FTile();
	Node.X = Index % Colums;
	Node.Y = Index / Colums;
	return Node;
}

FReturnItemAtIndex UACInventoryComponent::GetItemAtIndex(int Index)
{
	FReturnItemAtIndex RData;
	if(ItemDataArr.IsValidIndex(Index))
	{
		RData.valid = true;
		RData.ItemObjectData = ItemDataArr[Index].ItemObjectData;
	}
	else
	{
		RData.valid = false;
		RData.ItemObjectData = FItemData();
	}
	return RData;
}

TMap<FItemData, FTile> UACInventoryComponent::GetAllItems()
{
	TMap<FItemData, FTile> AllItem_Local;
	int Index = 0;

	for (FValidFirstItemData Data : ItemDataArr)
	{
		if (Data.ItemObjectData.IsValid() == true)
		{
			if (Data.first == true)
			{
				AllItem_Local.Add(Data.ItemObjectData, IndexToTile(Index));
			}
		}
		Index++;
	}
	return AllItem_Local;
}
