// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget/Game/Inventory/StoreInven/UWGridInventory.h"


void UUWGridInventory::NativeConstruct()
{
	Super::NativeConstruct();

	GridBorder = Cast<UBorder>(GetWidgetFromName(TEXT("GridBorder")));
	GridCanvas_Panel = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("GridCanvas_Panel")));
}

void UUWGridInventory::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}


void UUWGridInventory::Init(UACInventoryComponent* InventoryComponent, float Size)
{
	ACInventory = InventoryComponent;
	TileSize = Size;
	if (ACInventory != nullptr)
	{
		float SizeX = GetACInventory()->Colums * GetTileSize();
		float SizeY = GetACInventory()->Rows * GetTileSize();

		UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(GridBorder->Slot);
		CanvasSlot->SetSize(FVector2D(SizeX, SizeY));

		CreateLineSegments();
	}
}

void UUWGridInventory::CreateLineSegments()
{
	//Vertical
	for (int Index = 0; Index < GetACInventory()->Colums + 1; Index++)
	{
		float X_Local = Index * TileSize;
		FLine makeLine;
		makeLine.Start = FVector2D(X_Local, 0.0f);
		makeLine.End = FVector2D(X_Local, GetACInventory()->Rows * TileSize);
		
		LineArr.Add(makeLine);
	}
	//Horizantal
	for (int Index = 0; Index < GetACInventory()->Rows + 1; Index++)
	{
		float Y_Local = Index * TileSize;
		FLine makeLine;
		makeLine.Start = FVector2D(0.0f, Y_Local);
		makeLine.End = FVector2D(GetACInventory()->Colums * TileSize, Y_Local);

		LineArr.Add(makeLine);
	}	
}
