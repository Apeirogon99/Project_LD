// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Game/PS_Game.h"

APS_Game::APS_Game()
{

}

APS_Game::~APS_Game()
{
}

void APS_Game::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	/**Inventory Setting**/
	mColums = 6;		mRows = 15;
	mIsChange = false;

	/**Character Status Setting**/
	//Attack Range
	mAttackRange = 200.0f;		mAttackRadius = 50.0f;
	//Attack Info
	mIsAttacking = false;
	//Health
	mMaxHealth = 100.0f;		mCurrentHealth = 100.0f;
	//Mana
	mMaxMana = 100.0f;			mCurrentMana = 100.0f;
	//Character Level
	mCharacterLevel = 1;

	mIsAttacking = false;
}

void APS_Game::Destroyed()
{
	Super::Destroyed();

	OnInventoryChanged.Unbind();
}

void APS_Game::Init()
{
	mInventoryData.SetNum(mColums * mRows);
	for (int i = 0; i < mColums * mRows; i++)
	{
		mInventoryData[i] = NewObject<UItemObjectData>();
	}
}

void APS_Game::Init(const int64 inRemoteID)
{
	mRemoteID = inRemoteID;
}

int64 APS_Game::GetRemoteID()
{
	return mRemoteID;
}

void APS_Game::RemoveItem(UItemObjectData* ItemObjectData)
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
				mInventoryData[FIndex + SIndex * mColums] = NewObject<UItemObjectData>();
			}
		}

		int Index = 0;
		for (UItemObjectData*& Data : mInventoryObjectArr)
		{
			if (Data->position_x == ItemObjectData->position_x)
			{
				if (Data->position_y == ItemObjectData->position_y)
				{
					if (Data->ItemData.category_id == ItemObjectData->ItemData.category_id)
					{
						mInventoryObjectArr.RemoveAt(Index);
						break;
					}
				}
			}
			Index++;
		}
	}
	InventoryChangeDetected();
}

void APS_Game::AddItemAt(UItemObjectData* ItemObjectData, int TopLeftIndex)
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
				mInventoryObjectArr.Add(TileItemData);
			}
			mInventoryData[TileToIndex(LocalTile)]->ItemData = ItemObjectData->ItemData;
			mInventoryData[TileToIndex(LocalTile)]->position_x = LocalTile.X;
			mInventoryData[TileToIndex(LocalTile)]->position_y = LocalTile.Y;
		}
	}
	InventoryChangeDetected();
}

bool APS_Game::TryAddItem(UItemObjectData* ItemObjectData)
{
	if (ItemObjectData->IsValid() == true)
	{
		int itemIndex = 0;
		for (UItemObjectData*& itemData : mInventoryData)
		{
			if (IsRoomAvailable(ItemObjectData, itemIndex))
			{
				AddItemAt(ItemObjectData, itemIndex);
				return true;
			}
			itemIndex++;
		}

		ItemObjectData->Rotate();
		itemIndex = 0;
		for (UItemObjectData*& itemData : mInventoryData)
		{
			if (IsRoomAvailable(ItemObjectData, itemIndex))
			{
				AddItemAt(ItemObjectData, itemIndex);
				return true;
			}
			itemIndex++;
		}
		return false;
	}
	return false;
}

bool APS_Game::IsRoomAvailable(UItemObjectData* ItemObjectData, int TopLeftIndex)
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
				int  index = TileToIndex(LocalTile);

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

int APS_Game::TileToIndex(FTile Tile) const
{
	return Tile.X + Tile.Y * mColums;
}

FTile APS_Game::IndexToTile(int Index) const
{
	FTile Node = FTile();
	Node.X = Index % mColums;
	Node.Y = Index / mColums;
	return Node;
}

TArray<UItemObjectData*> APS_Game::GetAllItems()
{
	return mInventoryObjectArr;
}

bool APS_Game::GetItemAtIndex(int index, UItemObjectData*& ItemObject)
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

void APS_Game::InventoryChangeDetected()
{
	if (OnInventoryChanged.IsBound() == true)
	{
		OnInventoryChanged.ExecuteIfBound();
	}
}