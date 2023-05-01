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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Line") FVector2D Start;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Line") FVector2D End;
};

USTRUCT(BlueprintType)
struct PROJECT_LD_API FTile
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile") int32 X;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile") int32 Y;
};

USTRUCT(BlueprintType)
struct PROJECT_LD_API FReturnItemAtIndex
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Return") bool valid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Return") FItemData ItemObjectData;
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
	UFUNCTION(BlueprintCallable)
	void																	RemoveItem(FItemData& ItemObjectData);
	UFUNCTION(BlueprintCallable)
	void																	AddItemAt(FItemData& ItemObjectData, int TopLeftIndex);
	UFUNCTION(BlueprintCallable)
	bool																	TryAddItem(FItemData& ItemObjectData);
	UFUNCTION(BlueprintCallable)
	bool																	IsRoomAvailable(FItemData& ItemObjectData, int TopLeftIndex);
	UFUNCTION(BlueprintCallable)
	int																	TileToIndex(FTile Tile)	const;
	UFUNCTION(BlueprintCallable)
	FTile																IndexToTile(int Index)		const;
	UFUNCTION(BlueprintCallable)
	FReturnItemAtIndex									GetItemAtIndex(int Index);
	/*

private:
	//return Bool, ItemObjectData
	FItemData					GetItemAtIndex(int index);
	void								Init_EquipmentData();
	*/
};
