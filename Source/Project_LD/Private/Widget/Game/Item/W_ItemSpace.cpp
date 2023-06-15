// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Game/Item/W_ItemSpace.h"
#include "Widget/Game/Inventory/UWItem.h"
#include <Widget/Game/Equipment/UWEquipItem.h>

#include "Blueprint/DragDropOperation.h"

#include <Component/ACInventoryComponent.h>
#include "Components/CanvasPanelSlot.h"
#include "Components/CanvasPanel.h"
#include "Components/SizeBox.h"
#include "Components/Image.h"

#include <UObject/ConstructorHelpers.h>

#include <Struct/Game/GameDatas.h>

void UW_ItemSpace::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UW_ItemSpace::NativeConstruct()
{
	Super::NativeConstruct();

	TSubclassOf<UUWEquipItem> ImageWidgetAsset = StaticLoadClass(UUWEquipItem::StaticClass(), NULL, TEXT("WidgetBlueprint'/Game/Blueprint/Widget/Game/Inventory/Equipment/BW_EquipItem.BW_EquipItem_C'"));
	if (ImageWidgetAsset)
	{
		mImageAsset = ImageWidgetAsset;
	}

	ImgSlotFrame = Cast<UImage>(GetWidgetFromName(TEXT("ImgSlotFrame")));
	ImgSlot = Cast<UImage>(GetWidgetFromName(TEXT("ImgSlot")));
	ItemCanvas = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("ItemCanvas")));

	SlotSizeBox = Cast<USizeBox>(GetWidgetFromName(TEXT("SlotSizeBox")));
	if (SlotSizeBox)
	{
		SlotSizeBox->SetWidthOverride(mSizeX);
		SlotSizeBox->SetHeightOverride(mSizeY);
	}

	UTexture2D* Texture2DHelmet = LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/GameContent/GUI/Character_Profile_inventory/Player_EQ/Icons/T_Helmet_Icon.T_Helmet_Icon'"));
	//UTexture2D* Texture2DShoulder = LoadObject<UTexture2D>(nullptr, TEXT(""));
	UTexture2D* Texture2DChest = LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/GameContent/GUI/Character_Profile_inventory/Player_EQ/Icons/T_Armor_Icon.T_Armor_Icon'"));
	//UTexture2D* Texture2DBracers = LoadObject<UTexture2D>(nullptr, TEXT(""));
	//UTexture2D* Texture2DHands = LoadObject<UTexture2D>(nullptr, TEXT(""));
	//UTexture2D* Texture2DPants = LoadObject<UTexture2D>(nullptr, TEXT(""));
	UTexture2D* Texture2DBoots = LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/GameContent/GUI/Character_Profile_inventory/Player_EQ/Icons/T_Boots_Icon.T_Boots_Icon'"));

	UTexture2D* Texture2DLeftWeapon = LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/GameContent/GUI/Character_Profile_inventory/Player_EQ/Icons/T_Sword_Icon.T_Sword_Icon'"));
	//UTexture2D* Texture2DRightWeapon = LoadObject<UTexture2D>(nullptr, TEXT(""));

	if(Texture2DHelmet)
	{
		mTextureArr.Add(Texture2DHelmet);
	}
	/*
	if (Texture2DShoulder)
	{
		mTextureArr.Add(Texture2DShoulder);
	}
	*/
	if (Texture2DChest)
	{
		mTextureArr.Add(Texture2DChest);
	}
	/*
	if (Texture2DBracers)
	{
		mTextureArr.Add(Texture2DBracers);
	}
	if (Texture2DHands)
	{
		mTextureArr.Add(Texture2DHands);
	}
	if (Texture2DPants)
	{
		mTextureArr.Add(Texture2DPants);
	}
	*/
	if (Texture2DBoots)
	{
		mTextureArr.Add(Texture2DBoots);
	}
	if (Texture2DLeftWeapon)
	{
		mTextureArr.Add(Texture2DLeftWeapon);
	}
	/*
	if (Texture2DRightWeapon)
	{
		mTextureArr.Add(Texture2DRightWeapon);
	}
	*/
	if (mCategoryId != 0)
	{
		ImgSlot->SetBrushFromTexture(mTextureArr[2]);
		//ImgSlot->SetBrushFromTexture(mTextureArr[mCategoryId-1]);
	}

	bRigthItemCategory = false;
	bExist = false;
}

bool UW_ItemSpace::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	UDragDropOperation* Operation = Cast<UDragDropOperation>(InOperation);
	if (Operation)
	{
		UItemObjectData* ItemDataPayload = Cast<UItemObjectData>(Operation->Payload);
		if (ItemDataPayload)
		{
			if (ItemDataPayload->IsValid())
			{
				if (ItemDataPayload->ItemData.category_id == mCategoryId)
				{
					if (IsValid(mImageAsset))
					{
						if (!bExist)
						{
							bExist = true;

							UUWEquipItem* EquipmentItemSlot = Cast<UUWEquipItem>(CreateWidget(GetWorld(), mImageAsset));
							if (EquipmentItemSlot)
							{
								EquipmentItemSlot->Init();
								EquipmentItemSlot->OnEquipItemRemoved.BindUFunction(this, FName("FalseExist"));
								EquipmentItemSlot->mItemObjectData = ItemDataPayload;
								EquipmentItemSlot->SetImage();

								UCanvasPanelSlot* Local_CanvasSlot = Cast<UCanvasPanelSlot>(ItemCanvas->AddChild(EquipmentItemSlot));
								Local_CanvasSlot->SetAnchors(FAnchors(0.f, 0.f, 1.f, 1.f));
								Local_CanvasSlot->SetOffsets(FMargin(0.f, 0.f, 0.f, 0.f));

								//Item ÀåÂø
								UE_LOG(LogTemp, Warning, TEXT("%d Item Succ"), mCategoryId);
							}
						}
						else
						{
							FTile tile;
							tile.X = ItemDataPayload->position_x;
							tile.Y = ItemDataPayload->position_y;

							mInvenComponent->AddItemAt(ItemDataPayload, mInvenComponent->TileToIndex(tile));

							mInvenComponent->SetInventoryPacket(ItemDataPayload, EInventoryType::Update);

							UE_LOG(LogTemp, Warning, TEXT("%d Item Fail"), mCategoryId);
						}
					}
				}
				else
				{
					FTile tile;
					tile.X = ItemDataPayload->position_x;
					tile.Y = ItemDataPayload->position_y;

					mInvenComponent->AddItemAt(ItemDataPayload, mInvenComponent->TileToIndex(tile));

					mInvenComponent->SetInventoryPacket(ItemDataPayload, EInventoryType::Update);

					UE_LOG(LogTemp, Warning, TEXT("%d Item Fail"), mCategoryId);
				}
			}
		}
	}

	return true;
}

void UW_ItemSpace::Init(UACInventoryComponent* InvenComponent)
{
	mInvenComponent = InvenComponent;
}

void UW_ItemSpace::FalseExist()
{
	bExist = false;
}
