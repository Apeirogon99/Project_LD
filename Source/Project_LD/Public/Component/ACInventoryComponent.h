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
	void											ReplacePacket(UItemObjectData* InvenObjectData, UItemObjectData* EquipObejctData, int32 PartID);
	void											Refresh();
	void											ChangeInvenObjectArr();
	void											LoadItem(const google::protobuf::RepeatedPtrField<Protocol::SItem>& inItems);
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
		item->set_object_id(inItemData->ObjectID);
		item->set_item_code(inItemData->mItemCode);

		Protocol::SVector* worldPositon = item->mutable_world_position();
		FVector itemLocation = controller->GetPawn()->GetActorLocation();
		worldPositon->set_x(itemLocation.X);
		worldPositon->set_y(itemLocation.Y);
		worldPositon->set_z(itemLocation.Z);

		Protocol::SVector2D* invenPositon = item->mutable_inven_position();
		invenPositon->set_x(inItemData->position_x);
		invenPositon->set_y(inItemData->position_y);
		item->set_rotation(inItemData->rotation);

		SendBufferPtr sendBuffer = FGamePacketHandler::MakeSendBuffer(controller, inPacket);
		controller->Send(sendBuffer);
	}
};
