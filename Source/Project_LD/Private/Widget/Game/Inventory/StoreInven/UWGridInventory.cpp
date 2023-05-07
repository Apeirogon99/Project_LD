// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget/Game/Inventory/StoreInven/UWGridInventory.h"


void UUWGridInventory::NativeOnInitialized()
{
	UE_LOG(LogTemp, Warning, TEXT("Call UWGridInven NativeOnInitialized"));
}

void UUWGridInventory::testInit()
{
	if (ACInventory != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UWGrid ACInventory exist"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UWGrid ACInventory dosen't exist"));
	}
	if (GridBorder != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UWGrid GridBorder exist"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UWGrid GridBorder dosen't exist"));
	}
	if (GridCanvas_Panel != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UWGrid GridCanvas_Panel exist"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UWGrid GridCanvas_Panel dosen't exist"));
	}
}

void UUWGridInventory::Init(UACInventoryComponent* InventoryComponent, float Size)
{
	//ACInventory = InventoryComponent;
	//TileSize = Size;
	
	/*
	float SizeX = GetACInventory()->Colums * GetTileSize();
	float SizeY = GetACInventory()->Rows * GetTileSize();

	UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(GridBorder->Slot);
	CanvasSlot->SetSize(FVector2D(SizeX, SizeY));

	CreateLineSegments();
	*/
	//Setting();
}

void UUWGridInventory::CreateLineSegments()
{
	//Vertical
	for (int Index = 0; GetACInventory()->Colums + 1; Index++)
	{
		float X_Local = Index * TileSize;
		FLine makeLine;
		makeLine.Start = FVector2D(X_Local, 0.0f);
		makeLine.End = FVector2D(X_Local, GetACInventory()->Rows * TileSize);
		
		LineArr.Add(makeLine);
	}
	//Horizantal
	for (int Index = 0; GetACInventory()->Rows + 1; Index++)
	{
		float Y_Local = Index * TileSize;
		FLine makeLine;
		makeLine.Start = FVector2D(0.0f, Y_Local);
		makeLine.End = FVector2D(GetACInventory()->Colums * TileSize, Y_Local);

		LineArr.Add(makeLine);
	}
}
