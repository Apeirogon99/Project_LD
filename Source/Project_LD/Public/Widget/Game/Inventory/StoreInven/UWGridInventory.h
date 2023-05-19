// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
UCLASS()
class PROJECT_LD_API UUWGridInventory : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;
	virtual void NativeDestruct() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	
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

public:
	UFUNCTION(BlueprintCallable)
	void Init(UACInventoryComponent* InventoryComponent, float Size);

	UFUNCTION()
	void CreateLineSegments();

	UFUNCTION()
	void CallRemoved_Single(FItemData ItemData);

	UFUNCTION()
	void Refresh();

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