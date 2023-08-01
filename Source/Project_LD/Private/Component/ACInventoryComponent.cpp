// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/ACInventoryComponent.h"
#include "Framework/Gameinstance/LDGameInstance.h"
#include <Game/PS_Game.h>
#include <Game/GM_Game.h>
#include <Network/NetworkController.h>

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
		mInventoryData[i]->SetType(EItemObjectType::Inventory);
	}
}

//End -> 바인드 풀기
void UACInventoryComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (OnInventoryChanged.IsBound())
	{
		OnInventoryChanged.Unbind();
	}
	if (OnMoneyChanged.IsBound() == true)
	{
		OnMoneyChanged.Unbind();
	}
}

//GridInven에서 바인딩 된 델리게이트 호출
void UACInventoryComponent::Refresh()
{
	if (OnInventoryChanged.IsBound() == true)
	{
		ChangeInvenObjectArr();
		OnInventoryChanged.ExecuteIfBound();
	}
	if (OnMoneyChanged.IsBound() == true)
	{
		OnMoneyChanged.ExecuteIfBound();
	}
}

//ItemObjectData가 변하면 ItemInven초기화 후 다시 쏴줌
void UACInventoryComponent::ChangeInvenObjectArr()
{
	//mInventoryData.Empty();
	for (int i = 0; i < mColums * mRows; i++)
	{
		mInventoryData[i]->Clear();
		mInventoryData[i]->SetType(EItemObjectType::Inventory);
	}

	for (UItemObjectData* Data : mInventoryObjectArr)
	{	
		int X = Data->GetSize().X;
		int Y = Data->GetSize().Y;

		for (int XIndex = Data->GetPositionX(); XIndex < Data->GetPositionX() + X; XIndex++)
		{
			for (int YIndex = Data->GetPositionY(); YIndex < Data->GetPositionY() + Y; YIndex++)
			{
				FTile LocalTile = FTile();
				LocalTile.X = XIndex;
				LocalTile.Y = YIndex;

				mInventoryData[TileToIndex(LocalTile)]->SetObjectID(Data->GetObjectID());
				mInventoryData[TileToIndex(LocalTile)]->SetItemCode(Data->GetItemCode());
				mInventoryData[TileToIndex(LocalTile)]->SetItemData(Data->GetItemData());
				mInventoryData[TileToIndex(LocalTile)]->SetPositionX(LocalTile.X);
				mInventoryData[TileToIndex(LocalTile)]->SetPositionY(LocalTile.Y);
				mInventoryData[TileToIndex(LocalTile)]->SetRotation(Data->GetRotation());
			}
		}
	}
}

//서버에서 아이템 정보를 받아옴
void UACInventoryComponent::LoadItem(const google::protobuf::RepeatedPtrField<Protocol::SItem>& inItems, const int32& inMoney)
{
	ClearInventory();

	ULDGameInstance* Instance = Cast<ULDGameInstance>(GetWorld()->GetGameInstance());
	const int32 maxItemSize = inItems.size();
	for (int32 index = 0; index < maxItemSize; ++index)
	{
		UItemObjectData* ItemObjectData = NewObject<UItemObjectData>();

		const Protocol::SItem& curItem = inItems.Get(index);
		ItemObjectData->SetObjectID(curItem.object_id());
		ItemObjectData->SetItemCode(curItem.item_code());

		int32 Code = ItemObjectData->GetItemCode();
		FItemData* ItemTable = Instance->GetItemData(Code);
		ItemObjectData->SetItemData(*ItemTable);
	
		const Protocol::SVector2D& invenPosition = curItem.inven_position();
		ItemObjectData->SetPositionX(invenPosition.x());
		ItemObjectData->SetPositionY(invenPosition.y());
		ItemObjectData->SetRotation(curItem.rotation());
		ItemObjectData->SetType(EItemObjectType::Inventory);

		mInventoryObjectArr.Add(ItemObjectData);
	}

	this->mMoney = inMoney;

	Refresh();
}

//아이템 Inven, InvenObject 초기화
void UACInventoryComponent::ClearInventory()
{

	for (int i = 0; i < mColums * mRows; i++)
	{
		mInventoryData[i]->Clear();
		mInventoryData[i]->SetType(EItemObjectType::Inventory);
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
			if (Data->GetObjectID() == ItemObjectData->GetObjectID())
			{
				mInventoryObjectArr.RemoveAt(Index);
				break;
			}

			Index++;
		}
	}
	Refresh();
}

//아이템 습득
void UACInventoryComponent::AddItemAt(UItemObjectData* ItemObjectData, const int TopLeftIndex)
{
	FTile TileData = IndexToTile(TopLeftIndex);
	ItemObjectData->SetPositionX(TileData.X);
	ItemObjectData->SetPositionY(TileData.Y);
	mInventoryObjectArr.Add(ItemObjectData);
	Refresh();
}

//아이템 먹기 시도
bool UACInventoryComponent::TryAddItem(UItemObjectData* ItemObjectData)
{
	if (nullptr == ItemObjectData)
	{
		return false;
	}

	if (ItemObjectData->IsValid() == true)
	{
		//데이터 먹기
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

		//돌려서 먹어보기
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

//먹을 수 있는 공간인지 체크
bool UACInventoryComponent::IsRoomAvailable(UItemObjectData* ItemObjectData,const int TopLeftIndex)
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

//Tile값 -> Index값
int UACInventoryComponent::TileToIndex(const FTile Tile) const
{
	return Tile.X + Tile.Y * mColums;
}

//Index값 -> Tile값
FTile UACInventoryComponent::IndexToTile(const int Index) const
{
	FTile Node = FTile();
	Node.X = Index % mColums;
	Node.Y = Index / mColums;
	return Node;
}

//InvenObjectData 모두 가져오기
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

//배열의 해당 부분에 아이템 존재하는지  확인
bool UACInventoryComponent::GetItemAtIndex(const int index, UItemObjectData*& ItemObject)
{
	if (mInventoryData.IsValidIndex(index))
	{
		ItemObject = mInventoryData[index];
		return true;
	}
	else
	{
		ItemObject = NewObject<UItemObjectData>();
		ItemObject->SetType(EItemObjectType::Inventory);
		return false;
	}
	return false;
}

void UACInventoryComponent::ReplacePacket(UItemObjectData* InvenObjectData, UItemObjectData* EquipObejctData, int32 PartID)
{
	UWorld* world = GetWorld();
	if (world == nullptr)
	{
		return;
	}
	AGM_Game* gamemode = Cast<AGM_Game>(world->GetAuthGameMode());
	if (gamemode == nullptr)
	{
		return;
	}
	ANetworkController* controller = Cast<ANetworkController>(gamemode->GetNetworkController());
	if (controller)
	{
		Protocol::C2S_ReplaceEqipment replaceEqipment;

		const int64 serverTimeStamp = controller->GetServerTimeStamp();
		replaceEqipment.set_timestamp(serverTimeStamp);

		Protocol::SItem* insertInvenItem = replaceEqipment.mutable_insert_inven_item();
		insertInvenItem->set_object_id(InvenObjectData->GetObjectID());
		insertInvenItem->set_item_code(InvenObjectData->GetItemCode());

		Protocol::SVector2D* insertInvenItemPositon = insertInvenItem->mutable_inven_position();
		insertInvenItemPositon->set_x(InvenObjectData->GetPositionX());
		insertInvenItemPositon->set_y(InvenObjectData->GetPositionY());

		insertInvenItem->set_rotation(InvenObjectData->GetRotation());

		Protocol::SItem* insertEqipmentItem = replaceEqipment.mutable_insert_eqip_item();
		insertEqipmentItem->set_object_id(EquipObejctData->GetObjectID());
		insertEqipmentItem->set_item_code(EquipObejctData->GetItemCode());

		Protocol::SVector2D* insertEqipmentItemPositon = insertEqipmentItem->mutable_inven_position();
		insertEqipmentItemPositon->set_x(EquipObejctData->GetPositionX());
		insertEqipmentItemPositon->set_y(EquipObejctData->GetPositionY());

		replaceEqipment.set_part(static_cast<Protocol::ECharacterPart>(PartID));

		controller->Send(FGamePacketHandler::MakeSendBuffer(controller, replaceEqipment));
	}
}