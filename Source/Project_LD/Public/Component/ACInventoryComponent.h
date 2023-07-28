// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Struct/Game/GameDatas.h>
#include <Struct/Inventory/InventoryFrame.h>
#include <Protobuf/Handler/FClientPacketHandler.h>
#include <Protobuf/Handler/FGamePacketHandler.h>
#include "ACInventoryComponent.generated.h"

UENUM()
enum class EInventoryType
{
	Load,
	Insert,
	Update,
	Remove,
};


DECLARE_DELEGATE(FOnInventoryChanged);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_LD_API UACInventoryComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this component's properties
	UACInventoryComponent();

public:
	FOnInventoryChanged OnInventoryChanged;

public:
	FORCEINLINE int												GetColums() const							{ return mColums; }
	FORCEINLINE int												GetRows() const								{ return mRows; }
	FORCEINLINE TArray<UItemObjectData*>		GetInventoryData() const				{ return mInventoryData; }
	FORCEINLINE TArray<UItemObjectData*>		GetInventoryObjectArr() const		{ return mInventoryObjectArr; }

public:
	void SetColums(int Colums)																						{ mColums = Colums; }
	void SetRows(int Rows)																								{ mRows = Rows; }
	void SetInventoryData(TArray<UItemObjectData*> InventoryData)						{ mInventoryData = InventoryData; }
	void SetInventoryObejctArr(TArray<UItemObjectData*> InventoryObjectArr)		{ mInventoryObjectArr = InventoryObjectArr; }

public:
	void											ReplacePacket(UItemObjectData* InvenObjectData, UItemObjectData* EquipObejctData, int32 PartID);
	void											Refresh();
	void											ChangeInvenObjectArr();
	void											LoadItem(const google::protobuf::RepeatedPtrField<Protocol::SItem>& inItems, const int32& inMoney);
	void											ClearInventory();
	void											RemoveItem(UItemObjectData* ItemObjectData);
	void											AddItemAt(UItemObjectData* ItemObjectData, const int TopLeftIndex);
	bool											TryAddItem(UItemObjectData* ItemObjectData);
	bool											IsRoomAvailable(UItemObjectData* ItemObjectData, const int TopLeftIndex);
	bool											GetItemAtIndex(const int index, UItemObjectData*& ItemObject);
	int											TileToIndex(const FTile Tile)	const;
	FTile										IndexToTile(const int Index)		const;
	TArray<UItemObjectData*>	GetAllItems();

	void SetInventoryPacket(const UItemObjectData* inItemData, const EInventoryType& inType);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	template<typename T>
	void InventoryPacket(const UItemObjectData* inItemData)
	{
		UWorld* world = GetWorld();
		if (nullptr == world)
		{
			return;
		}

		ANetworkGameMode* gameMode = Cast<ANetworkGameMode>(world->GetAuthGameMode());
		if (nullptr == gameMode)
		{
			return;
		}

		ANetworkController* controller = gameMode->GetNetworkController();
		if (nullptr == controller)
		{
			return;
		}

		T inPacket;
		inPacket.set_timestamp(controller->GetServerTimeStamp());

		Protocol::SItem* item = inPacket.mutable_item();
		item->set_object_id(inItemData->GetObjectID());
		item->set_item_code(inItemData->GetItemCode());

		Protocol::SVector* worldPositon = item->mutable_world_position();
		FVector itemLocation = controller->GetPawn()->GetActorLocation();
		worldPositon->set_x(itemLocation.X);
		worldPositon->set_y(itemLocation.Y);
		worldPositon->set_z(itemLocation.Z);

		Protocol::SVector2D* invenPositon = item->mutable_inven_position();
		invenPositon->set_x(inItemData->GetPositionX());
		invenPositon->set_y(inItemData->GetPositionY());
		item->set_rotation(inItemData->GetRotation());

		SendBufferPtr sendBuffer = FGamePacketHandler::MakeSendBuffer(controller, inPacket);
		controller->Send(sendBuffer);
	}

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Constants", meta = (AllowPrivateAccess = "true")) int mColums;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Constants", meta = (AllowPrivateAccess = "true")) int mRows;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<UItemObjectData*> mInventoryData;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<UItemObjectData*> mInventoryObjectArr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 mMoney;
};
