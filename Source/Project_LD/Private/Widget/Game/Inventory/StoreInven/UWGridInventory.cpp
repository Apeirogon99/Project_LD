// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget/Game/Inventory/StoreInven/UWGridInventory.h"
#include "Widget/Game/Inventory/UWItem.h"
#include "Components/CanvasPanelSlot.h"


void UUWGridInventory::NativeConstruct()
{
	Super::NativeConstruct();

	static ConstructorHelpers::FClassFinder<UUserWidget> ImageWidgetAsset(TEXT("WidgetBlueprint'/Game/TestFolder/TestCharacter/widget/BW_Item.BW_Item_C'"));
	if (ImageWidgetAsset.Succeeded())
	{
		ImageAsset = ImageWidgetAsset.Class;
	}

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

		Refresh();

		ACInventory->OnInventoryChanged.AddUFunction(this, FName("Refresh"));
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

void UUWGridInventory::CallRemoved_Single(FItemData ItemData)
{
	ACInventory->RemoveItem(ItemData);
}

void UUWGridInventory::Refresh()
{
	GridCanvas_Panel->ClearChildren();
	TMap<FItemData, FTile> AllItem = ACInventory->GetAllItems();
	for (TPair<FItemData, FTile> Data : AllItem)
	{
		if (IsValid(ImageAsset))
		{
			UUWItem* ItemImageWidget = Cast<UUWItem>(CreateWidget(GetWorld(), ImageAsset));
			if (ItemImageWidget)
			{
				ItemImageWidget->TileSize = TileSize;
				ItemImageWidget->ItemData = Data.Key;

				//Bind Remove
				ItemImageWidget->OnRemoved.AddUFunction(this, FName("CallRemoved_Single"));
				
				UCanvasPanelSlot* Local_Slot = Cast<UCanvasPanelSlot>(GridCanvas_Panel->AddChild(ItemImageWidget));
				Local_Slot->SetAutoSize(true);

				float X = Data.Value.X * TileSize;
				float Y = Data.Value.Y * TileSize;
				Local_Slot->SetPosition(FVector2D(X, Y));
			}
		}
	}
}
