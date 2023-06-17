// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/ACInventoryComponent.h"
#include "Framework/Gameinstance/LDGameInstance.h"
#include <Game/PS_Game.h>
#include <Game/GM_Game.h>

// Sets default values for this component's properties
UACInventoryComponent::UACInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	mColums = 12;
	mRows = 7;
}


// Called when the game starts
void UACInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	//ItemArr resize
	mInventoryData.SetNum(mColums * mRows);
	for (int i = 0; i < mColums * mRows; i++)
	{
		mInventoryData[i] = NewObject<UItemObjectData>();
	}
}

void UACInventoryComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (OnInventoryChanged.IsBound())
	{
		OnInventoryChanged.Unbind();
	}
}

void UACInventoryComponent::Refresh()
{
	if (OnInventoryChanged.IsBound() == true)
	{
		ChangeInvenObjectArr();
		OnInventoryChanged.ExecuteIfBound();
	}
}

void UACInventoryComponent::ChangeInvenObjectArr()
{
	//mInventoryData.Empty();
	for (int i = 0; i < mColums * mRows; i++)
	{
		mInventoryData[i]->Clear();
	}

	for (UItemObjectData* Data : mInventoryObjectArr)
	{
		int X = Data->GetSize().X;
		int Y = Data->GetSize().Y;

		for (int XIndex = Data->position_x; XIndex < Data->position_x + X; XIndex++)
		{
			for (int YIndex = Data->position_y; YIndex < Data->position_y + Y; YIndex++)
			{
				FTile LocalTile = FTile();
				LocalTile.X = XIndex;
				LocalTile.Y = YIndex;

				mInventoryData[TileToIndex(LocalTile)]->ObjectID = Data->ObjectID;
				mInventoryData[TileToIndex(LocalTile)]->mItemCode = Data->mItemCode;
				mInventoryData[TileToIndex(LocalTile)]->ItemData = Data->ItemData;
				mInventoryData[TileToIndex(LocalTile)]->position_x = LocalTile.X;
				mInventoryData[TileToIndex(LocalTile)]->position_y = LocalTile.Y;
				mInventoryData[TileToIndex(LocalTile)]->rotation = Data->rotation;
			}
		}
	}
}

void UACInventoryComponent::LoadItem(const google::protobuf::RepeatedPtrField<Protocol::SItem>& inItems)
{
	ClearInventory();

	ULDGameInstance* Instance = Cast<ULDGameInstance>(GetWorld()->GetGameInstance());
	const int32 maxItemSize = inItems.size();
	for (int32 index = 0; index < maxItemSize; ++index)
	{
		UItemObjectData* ItemObjectData = NewObject<UItemObjectData>();

		const Protocol::SItem& curItem = inItems.Get(index);
		ItemObjectData->ObjectID	= curItem.object_id();
		ItemObjectData->mItemCode	= curItem.item_code();

		FItemData* ItemTable = Instance->GetItemData(ItemObjectData->mItemCode);
		ItemObjectData->ItemData	= *ItemTable;

		const Protocol::SVector2D& invenPosition = curItem.inven_position();
		ItemObjectData->position_x	= invenPosition.x();
		ItemObjectData->position_y	= invenPosition.y();
		ItemObjectData->rotation	= curItem.rotation();

		mInventoryObjectArr.Add(ItemObjectData);
	}

	Refresh();
}

void UACInventoryComponent::ClearInventory()
{

	for (int i = 0; i < mColums * mRows; i++)
	{
		mInventoryData[i]->Clear();
	}

	mInventoryObjectArr.Empty();
}

void UACInventoryComponent::RemoveItem(UItemObjectData* ItemObjectData)
{
	if (ItemObjectData->IsValid() == true)
	{

		int Index = 0;
		for (UItemObjectData*& Data : mInventoryObjectArr)
		{
			if (Data->ObjectID == ItemObjectData->ObjectID)
			{
				mInventoryObjectArr.RemoveAt(Index);
				break;
			}

			Index++;
		}
	}
	Refresh();
}

void UACInventoryComponent::AddItemAt(UItemObjectData* ItemObjectData, int TopLeftIndex)
{
	FTile TileData = IndexToTile(TopLeftIndex);
	ItemObjectData->position_x = TileData.X;
	ItemObjectData->position_y = TileData.Y;
	mInventoryObjectArr.Add(ItemObjectData);
	Refresh();
}

bool UACInventoryComponent::TryAddItem(UItemObjectData* ItemObjectData)
{
	if (nullptr == ItemObjectData)
	{
		return false;
	}

	if(ItemObjectData->IsValid() == true)
	{
		int itemIndex = 0;
		for (UItemObjectData*& itemData : mInventoryData)
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
		for (UItemObjectData*& itemData : mInventoryData)
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
			if ((FIndex >= 0) && (SIndex >= 0) && (FIndex < mColums) && (SIndex < mRows))
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
	return Tile.X + Tile.Y * mColums;
}

FTile UACInventoryComponent::IndexToTile(int Index) const
{
	FTile Node = FTile();
	Node.X = Index % mColums;
	Node.Y = Index / mColums;
	return Node;
}

TArray<UItemObjectData*> UACInventoryComponent::GetAllItems()
{
	return mInventoryObjectArr;
}

void UACInventoryComponent::SetInventoryPacket(const UItemObjectData* inItemData, const EInventoryType& inType)
{
	switch (inType)
	{
	case EInventoryType::Insert:
		InventoryPacket<Protocol::C2S_InsertInventory>(inItemData);
		break;
	case EInventoryType::Update:
		InventoryPacket<Protocol::C2S_UpdateInventory>(inItemData);
		break;
	case EInventoryType::Remove:
		InventoryPacket<Protocol::C2S_DeleteInventory>(inItemData);
		break;
	default:
		break;
	}
}

bool UACInventoryComponent::GetItemAtIndex(int index, UItemObjectData*& ItemObject)
{
	if (mInventoryData.IsValidIndex(index))
	{
		ItemObject = mInventoryData[index];
		return true;
	}
	else
	{
		ItemObject = NewObject<UItemObjectData>();
		return false;
	}
	return false;
}
