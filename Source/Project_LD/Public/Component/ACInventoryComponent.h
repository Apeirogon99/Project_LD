// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Struct/Game/GameDatas.h>
#include "Components/ActorComponent.h"
#include "ACInventoryComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnInventoryChanged);

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

	FTile() : X(0), Y(0) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile") int32 X;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile") int32 Y;
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
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Constants") int Colums;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Constants") int Rows;
	
	FOnInventoryChanged OnInventoryChanged;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UItemObjectData*> InventoryData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UItemObjectData*> InventoryObjectArr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsChange;

public:
	UFUNCTION(BlueprintCallable)
	void																	RemoveItem(UItemObjectData* ItemObjectData);
	UFUNCTION(BlueprintCallable)
	void																	AddItemAt(UItemObjectData* ItemObjectData, int TopLeftIndex);
	UFUNCTION(BlueprintCallable)
	bool																	TryAddItem(UItemObjectData* ItemObjectData);
	UFUNCTION(BlueprintCallable)
	bool																	IsRoomAvailable(UItemObjectData* ItemObjectData, int TopLeftIndex);
	UFUNCTION(BlueprintCallable)
	int																	TileToIndex(FTile Tile)	const;
	UFUNCTION(BlueprintCallable)
	FTile																IndexToTile(int Index)		const;
	UFUNCTION(BlueprintCallable)
	TArray<UItemObjectData*>							GetAllItems();
};
