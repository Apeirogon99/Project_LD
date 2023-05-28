// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ACInventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_LD_API UACInventoryComponent : public UActorComponent
{
	GENERATED_BODY()
	/*
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Constants") int mColums;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Constants") int mRows;
	
	FOnInventoryChanged OnInventoryChanged;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UItemObjectData*> mInventoryData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UItemObjectData*> mInventoryObjectArr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool mIsChange;

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
	UFUNCTION(BlueprintCallable)
	bool																	GetItemAtIndex(int index, UItemObjectData*& ItemObject);*/
};
