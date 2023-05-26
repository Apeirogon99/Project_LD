// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Struct/Game/GameDatas.h>
#include <Component/ACInventoryComponent.h>
#include <UMG/Public/Components/Border.h>
#include <UMG/Public/Components/CanvasPanel.h>
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanelSlot.h"
#include "Kismet/GameplayStatics.h"
#include "Containers/Array.h"
#include "UWGridInventory.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct PROJECT_LD_API FMousePositionReturn
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Position") bool Right;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Position") bool Down;
};

UCLASS()
class PROJECT_LD_API UUWGridInventory : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;
	virtual void NativeDestruct() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual FReply NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual bool NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = GetACInventory, Category = "Component")
	UACInventoryComponent* ACInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = GetTileSize, BlueprintSetter = SetTileSize, Category = "Default", meta = (AllowPrivateAccess = "true"))
	float TileSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (AllowPrivateAccess = "true"))
	TArray<FLine> LineArr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Panel", meta = (BindWidget))
	UBorder* GridBorder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Panel", meta = (BindWidget))
	UCanvasPanel* GridCanvas_Panel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Panel")
	TSubclassOf<UUserWidget> ImageAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drag Drop")
	bool DrawDropLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drag Drop")
	FIntPoint DraggedItemTopLeftTile;

public:
	UFUNCTION(BlueprintCallable)
	void Init(UACInventoryComponent* InventoryComponent, float Size);

	UFUNCTION(BlueprintCallable)
	void CreateLineSegments();

	UFUNCTION(BlueprintCallable)
	void CallRemoved_Single(UItemObjectData*& ItemData);

	UFUNCTION(BlueprintCallable)
	void Refresh();

	UFUNCTION(BlueprintCallable)
	void GetPayload(UDragDropOperation* Operator, UItemObjectData*& Payload) const;

	UFUNCTION(BlueprintCallable)
	bool IsRoomAvailableForPayload(UItemObjectData* Payload) const;

	UFUNCTION(BlueprintCallable)
	FMousePositionReturn MousePositionInTile(FVector2D MousePosition);

public:
	UFUNCTION(BlueprintSetter)
	void SetTileSize(float size) { this->TileSize = size; }

	UFUNCTION(BlueprintGetter)
	float GetTileSize() const { return TileSize; }

	UFUNCTION(BlueprintGetter)
	TArray<FLine> GetLineArr() { return LineArr; }

	UFUNCTION(BlueprintGetter)
	UACInventoryComponent* GetACInventory() { return ACInventory; }
};