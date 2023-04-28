// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Struct/Game/GameDatas.h>
#include "Components/ActorComponent.h"
#include "ACInventoryComponent.generated.h"

USTRUCT(BlueprintType)
struct PROJECT_LD_API FLine
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Line) FVector2D Start;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Line) FVector2D End;
};

USTRUCT(BlueprintType)
struct PROJECT_LD_API FTile
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tile) int32 X;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tile) int32 Y;
};

struct ReturnItemAtIndex
{
	bool valid;
	FItemData ItemObjectData;
};

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

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Constants") int Colums;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Constants") int Rows;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = GetItemDataArr, meta = (AllowPrivateAccess = "true"))
	TArray<FItemData> ItemDataArr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetIsChange, BlueprintGetter = GetIsChange, meta = (AllowPrivateAccess = "true"))
	bool IsChange;
	
public:
	//Getter
	UFUNCTION(BlueprintGetter)
	bool GetIsChange() const { return IsChange; }
	
	UFUNCTION(BlueprintGetter)
	TArray<FItemData> GetItemDataArr() { return ItemDataArr; }

	//Setter
	UFUNCTION(BlueprintSetter)
	void SetIsChange(bool Change) { IsChange = Change; }

public:
	void																	AddItemAt(FItemData ItemObjectData, int TopLeftIndex);
	bool																	TryAddItem(FItemData ItemObjectData);
	bool																	IsRoomAvailable(FItemData ItemObjectData, int TopLeftIndex);
	int																	TileToIndex(FTile Tile)	const;
	FTile																IndexToTile(int Index)		const;
	ReturnItemAtIndex											GetItemAtIndex(int Index);
	/*
public:
	void																	RemoveItem(FItemData ItemData);
	TArray<TMap<FItemData, FTile>>				GetAllItems();
	TArray<FItemData>										GetItems() const;
	TArray<FEquipmentData>								GetEquipment() const;

private:
	//return Bool, ItemObjectData
	FItemData					GetItemAtIndex(int index);
	void								Init_EquipmentData();
	*/
};
