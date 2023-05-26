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
	InventoryData.SetNum(Colums * Rows + 1);
	for (int i = 0; i < Colums * Rows + 1; i++)
	{
		InventoryData[i] = NewObject<UItemObjectData>();
	}
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

void UACInventoryComponent::RemoveItem(UItemObjectData* ItemObjectData)
{
	if (ItemObjectData->IsValid() == true)
	{
		int X = ItemObjectData->position_x;
		int Y = ItemObjectData->position_y;
		int sizeX = ItemObjectData->GetSize().X;
		int sizeY = ItemObjectData->GetSize().Y;

		for (int FIndex = X; FIndex < X + sizeX; FIndex++)
		{
			for (int SIndex = Y; SIndex < Y + sizeY; SIndex++)
			{
				InventoryData[FIndex + SIndex * Colums] = NewObject<UItemObjectData>();
			}
		}

		int Index = 0;
		for (UItemObjectData*& Data : InventoryObjectArr)
		{
			if (Data->position_x == ItemObjectData->position_x)
			{
				if (Data->position_y == ItemObjectData->position_y)
				{
					if (Data->ItemData.category_id == ItemObjectData->ItemData.category_id)
					{
						InventoryObjectArr.RemoveAt(Index);
						break;
					}
				}
			}
			Index++;
		}
	}
}

void UACInventoryComponent::AddItemAt(UItemObjectData* ItemObjectData, int TopLeftIndex)
{
	FTile TileData = IndexToTile(TopLeftIndex);
	int X = ItemObjectData->GetSize().X;
	int Y = ItemObjectData->GetSize().Y;

	for (int FIndex = TileData.X; FIndex < TileData.X + X; FIndex++)
	{
		for (int SIndex = TileData.Y; SIndex < TileData.Y + Y; SIndex++)
		{
			FTile LocalTile = FTile();
			LocalTile.X = FIndex;
			LocalTile.Y = SIndex;

			if ((FIndex == TileData.X) && (SIndex == TileData.Y))
			{
				UItemObjectData* TileItemData = ItemObjectData;
				TileItemData->position_x = LocalTile.X;
				TileItemData->position_y = LocalTile.Y;
				InventoryObjectArr.Add(TileItemData);
			}
			InventoryData[TileToIndex(LocalTile)]->ItemData = ItemObjectData->ItemData;
			InventoryData[TileToIndex(LocalTile)]->position_x = LocalTile.X;
			InventoryData[TileToIndex(LocalTile)]->position_y = LocalTile.Y;
		}
	}
	IsChange = true;
}

bool UACInventoryComponent::TryAddItem(UItemObjectData* ItemObjectData)
{
	if(ItemObjectData->IsValid() == true)
	{
		int itemIndex = 0;
		for (UItemObjectData*& itemData : InventoryData)
		{
			if(IsRoomAvailable(ItemObjectData,itemIndex))
			{
				AddItemAt(ItemObjectData,itemIndex);
				return true;	
			}
			itemIndex++;
		}
		
		ItemObjectData->Rotate();
		itemIndex = 0;
		for (UItemObjectData*& itemData : InventoryData)
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

bool UACInventoryComponent::IsRoomAvailable(UItemObjectData* ItemObjectData, int TopLeftIndex)
{
	FTile TileData = IndexToTile(TopLeftIndex);
	int X = ItemObjectData->GetSize().X;
	int Y = ItemObjectData->GetSize().Y;

	for (int FIndex = TileData.X; FIndex < TileData.X + X; FIndex++)
	{
		for (int SIndex = TileData.Y; SIndex < TileData.Y + Y; SIndex++)
		{
			if ((FIndex >= 0) && (SIndex >= 0) && (FIndex < Colums) && (SIndex < Rows))
			{
				FTile LocalTile = FTile();
				LocalTile.X = FIndex;
				LocalTile.Y = SIndex;
	
				UItemObjectData* Data = NewObject<UItemObjectData>();
				int  index =TileToIndex(LocalTile);
				
				if (GetItemAtIndex(index, Data))
				{
					if (Data->IsValid())
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

TArray<UItemObjectData*> UACInventoryComponent::GetAllItems()
{
	return InventoryObjectArr;
}

bool UACInventoryComponent::GetItemAtIndex(int index, UItemObjectData*& ItemObject)
{
	if (InventoryData.IsValidIndex(index))
	{
		ItemObject = InventoryData[index];
		return true;
	}
	else
	{
		ItemObject = NewObject<UItemObjectData>();
		return false;
	}
	return false;
}
