// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Game/Item/W_ItemSpace.h"
#include "Widget/Game/Inventory/UWItem.h"
#include <Widget/Game/Equipment/UWEquipItem.h>

#include "Blueprint/DragDropOperation.h"

#include <Component/ACEquipment.h>
#include <Component/ACInventoryComponent.h>
#include "Components/CanvasPanelSlot.h"
#include "Components/CanvasPanel.h"
#include "Components/Border.h"
#include "Components/SizeBox.h"
#include "Components/Image.h"

#include <UObject/ConstructorHelpers.h>
#include <Framework/Game/NPS_Game.h>

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
	else
	{
		return;
	}

	ItemCanvas = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("ItemCanvas")));
	categoryBorder = Cast<UBorder>(GetWidgetFromName(TEXT("categoryBorder")));
	ImgSlotFrame = Cast<UImage>(GetWidgetFromName(TEXT("ImgSlotFrame")));
	ImgSlot = Cast<UImage>(GetWidgetFromName(TEXT("ImgSlot")));

	SlotSizeBox = Cast<USizeBox>(GetWidgetFromName(TEXT("SlotSizeBox")));
	if (SlotSizeBox)
	{
		SlotSizeBox->SetWidthOverride(mSizeX);
		SlotSizeBox->SetHeightOverride(mSizeY);
	}

	UTexture2D* Texture2DHelmet = LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/GameContent/GUI/InventoryItemImage/T_HelmetSlot.T_HelmetSlot'"));
	UTexture2D* Texture2DShoulder = LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/GameContent/GUI/InventoryItemImage/T_SholderSlot.T_SholderSlot'"));
	UTexture2D* Texture2DChest = LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/GameContent/GUI/InventoryItemImage/T_ArmorSlot.T_ArmorSlot'"));
	UTexture2D* Texture2DBracers = LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/GameContent/GUI/InventoryItemImage/T_BeltSlot.T_BeltSlot'"));
	UTexture2D* Texture2DHands = LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/GameContent/GUI/InventoryItemImage/T_GlovesSlot.T_GlovesSlot'"));
	UTexture2D* Texture2DPants = LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/GameContent/GUI/InventoryItemImage/T_PantsSlot.T_PantsSlot'"));
	UTexture2D* Texture2DBoots = LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/GameContent/GUI/InventoryItemImage/T_BootsSlot.T_BootsSlot'"));

	UTexture2D* Texture2DLeftWeapon = LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/GameContent/GUI/InventoryItemImage/T_WeaponSlot.T_WeaponSlot'"));
	UTexture2D* Texture2DRightWeapon = LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/GameContent/GUI/InventoryItemImage/T_WeaponSlot.T_WeaponSlot'"));

	if (Texture2DHelmet)
	{
		mTextureArr.Add(Texture2DHelmet);
	}
	if (Texture2DShoulder)
	{
		mTextureArr.Add(Texture2DShoulder);
	}
	if (Texture2DChest)
	{
		mTextureArr.Add(Texture2DChest);
	}
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
	if (Texture2DBoots)
	{
		mTextureArr.Add(Texture2DBoots);
	}
	if (Texture2DLeftWeapon)
	{
		mTextureArr.Add(Texture2DLeftWeapon);
	}
	if (Texture2DRightWeapon)
	{
		mTextureArr.Add(Texture2DRightWeapon);
	}

	if (mCategoryId != 0)
	{
		ImgSlot->SetBrushFromTexture(mTextureArr[mCategoryId - 1]);
	}

	bRigthItemCategory = false;
	bExist = false;
}

void UW_ItemSpace::NativeDestruct()
{
	Super::NativeDestruct();
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
				//���� ī�װ� Ȯ��
				if (ItemDataPayload->GetItemData().GetCategoryID() == mCategoryId)
				{
					if (IsValid(mImageAsset))
					{
						if (!bExist)
						{
							//������ â�� ������� -> ������ ����
							bExist = true;

							CreateItemWidget(ItemDataPayload);

							mEquipmentComponent->GetEquipmentObjectData()[mCategoryId - 1] = mEquipmentItemSlot->GetItemObjectData();

							mInvenComponent->ReplacePacket(NewObject<UItemObjectData>(), ItemDataPayload, mCategoryId);
						}
						else
						{
							//������ â�� �������� �̹� ����
							if (mEquipmentItemSlot != nullptr)
							{
								if (mInvenComponent->TryAddItem(mEquipmentItemSlot->GetItemObjectData()))
								{
									//������ ��� �������� �κ��丮�� �� �� �ִ� ��� -> ���� ������ �κ��丮�� ����
									UItemObjectData* OldItemData = mEquipmentItemSlot->GetItemObjectData();
									ItemCanvas->ClearChildren();

									if (mEquipmentItemSlot)
									{
										CreateItemWidget(ItemDataPayload);

										mEquipmentComponent->GetEquipmentObjectData()[mCategoryId - 1] = mEquipmentItemSlot->GetItemObjectData();

										mInvenComponent->ReplacePacket(OldItemData, ItemDataPayload, mCategoryId);
									}
								}
								else
								{
									//���â�� �������� �κ��丮�� ���ư� �� ���� ��� -> ���� �õ� ������ �κ��丮�� ����
									FTile tile;
									tile.X = ItemDataPayload->GetPositionX();
									tile.Y = ItemDataPayload->GetPositionY();

									mInvenComponent->AddItemAt(ItemDataPayload, mInvenComponent->TileToIndex(tile));
								}
							}
						}
					}
				}
				else
				{
					//ī�װ��� �ٸ� ���
					if (ItemDataPayload->GetType() == EItemObjectType::Equipment)
					{
						//��� â���� �̵��� ���
						int Index = ItemDataPayload->GetItemData().GetCategoryID() - 1;

						mEquipmentComponent->GetEquipmentObjectData()[Index] = ItemDataPayload;
						mEquipmentComponent->GetEquipmentWidget()[Index]->ReMakeWidget(ItemDataPayload);
					}
					else if (ItemDataPayload->GetType() == EItemObjectType::Inventory)
					{
						//�κ��丮���� �� ���
						FTile tile;
						tile.X = ItemDataPayload->GetPositionX();
						tile.Y = ItemDataPayload->GetPositionY();

						mInvenComponent->AddItemAt(ItemDataPayload, mInvenComponent->TileToIndex(tile));
					}
				}
			}
		}
	}
	mEquipmentComponent->DropItemWidget();

	return true;
}

void UW_ItemSpace::Init(UACInventoryComponent* InvenComponent, UACEquipment* EquipmentComponent)
{
	mInvenComponent = InvenComponent;
	if (mInvenComponent == nullptr)
	{
		return; 
	}
	mEquipmentComponent = EquipmentComponent;
	if (mEquipmentComponent == nullptr)
	{
		return;
	}
}

void UW_ItemSpace::FalseExist()
{
	bExist = false;
}

void UW_ItemSpace::Refresh(UItemObjectData* ItemObjectData)
{
	ItemCanvas->ClearChildren();

	bExist = true;

	CreateItemWidget(ItemObjectData);
}

void UW_ItemSpace::ReMakeWidget(UItemObjectData* ItemObjectData)
{
	if (mEquipmentItemSlot)
	{
		CreateItemWidget(ItemObjectData);

		mEquipmentComponent->GetEquipmentObjectData()[mCategoryId - 1] = mEquipmentItemSlot->GetItemObjectData();
	}
}

void UW_ItemSpace::CreateItemWidget(UItemObjectData* ItemObjectData)
{
	APlayerController* controller = GetOwningPlayer();
	if (controller == nullptr)
	{
		return;
	}
	ANPS_Game* playerState = controller->GetPlayerState<ANPS_Game>();
	if (playerState == nullptr)
	{
		return;
	}

	mEquipmentItemSlot = Cast<UUWEquipItem>(CreateWidget(GetWorld(), mImageAsset));
	if (mEquipmentItemSlot)
	{
		mEquipmentItemSlot->Init();
		mEquipmentItemSlot->SetFrameSize(mSizeX, mSizeY);
		mEquipmentItemSlot->OnEquipItemRemoved.BindUFunction(this, FName("FalseExist"));
		mEquipmentItemSlot->SetItemObjectData(ItemObjectData);
		mEquipmentItemSlot->GetItemObjectData()->SetType(EItemObjectType::Equipment);
		mEquipmentItemSlot->SetImage();

		UCanvasPanelSlot* Local_CanvasSlot = Cast<UCanvasPanelSlot>(ItemCanvas->AddChild(mEquipmentItemSlot));
		Local_CanvasSlot->SetAnchors(FAnchors(0.f, 0.f, 1.f, 1.f));
		Local_CanvasSlot->SetOffsets(FMargin(0.f, 0.f, 0.f, 0.f));
	
		playerState->calculationStats();
	}
}
