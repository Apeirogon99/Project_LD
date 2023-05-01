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


// Called every frame
void UACInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsChange)
	{
		IsChange = false;

		//Inventory Change event
		//델리게이트 이용해서 인벤토리 변화 감지
	}
}

void UACInventoryComponent::RemoveItem(FItemData& ItemObjectData)
{
	if (ItemObjectData.ValidData == true)
	{
		int itemIndex = 0;
		for (FItemData& itemData : ItemDataArr)
		{
			if (itemData == ItemObjectData)
			{
				ItemDataArr[itemIndex] = FItemData();
				IsChange = true;
			}
			itemIndex++;
		}
	}
}

void UACInventoryComponent::AddItemAt(FItemData& ItemObjectData, int TopLeftIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Call AddItemAt"));
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
			ItemDataArr[TileToIndex(LocalTile)] = ItemObjectData;
		}
	}
	IsChange = true;
}

bool UACInventoryComponent::TryAddItem(FItemData& ItemObjectData)
{
	UE_LOG(LogTemp, Warning, TEXT("Call TryAddItem"));
	if(ItemObjectData.ValidData == true)
	{
		int itemIndex = 0;
		for (FItemData& itemData : ItemDataArr)
		{
			if(IsRoomAvailable(ItemObjectData,itemIndex))
			{
				AddItemAt(ItemObjectData,itemIndex);
				return true;
			}
			itemIndex++;
		}
		FItemData RotatedItemObjectData = ItemObjectData;
		RotatedItemObjectData.rotation = 1;
		itemIndex = 0;
		for (FItemData& itemData : ItemDataArr)
		{
			if(IsRoomAvailable(RotatedItemObjectData,itemIndex))
			{
				AddItemAt(RotatedItemObjectData,itemIndex);
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
	UE_LOG(LogTemp, Warning, TEXT("Call IsRoomAvailable"));
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
					if (Data.ItemObjectData.ValidData == true)
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
		RData.ItemObjectData = ItemDataArr[Index];
	}
	else
	{
		RData.valid = false;
		RData.ItemObjectData = FItemData();
	}
	return RData;
}

