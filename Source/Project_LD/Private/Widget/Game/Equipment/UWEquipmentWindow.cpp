// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Game/Equipment/UWEquipmentWindow.h"
#include "Blueprint/DragDropOperation.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"

#include <Component/ACInventoryComponent.h>

void UUWEquipmentWindow::NativeConstruct()
{
	Super::NativeConstruct();

	Btn_OpenState = Cast<UButton>(GetWidgetFromName(TEXT("Btn_OpenState")));
	StateButtonIcon = Cast<UImage>(GetWidgetFromName(TEXT("StateButtonIcon")));
	StatusCanvas = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("StatusCanvas")));

	if (Btn_OpenState && StateButtonIcon && StatusCanvas)
	{
		Btn_OpenState->OnClicked.AddDynamic(this, &UUWEquipmentWindow::OpenStatus);
	}

	TB_SName = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_SName")));

	TB_SAttackDamage = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_SAttackDamage")));
	TB_SAttackDamageGrowthValue = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_SAttackDamageGrowthValue")));
	
	TB_SArmor = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_SArmor")));
	TB_SArmorGrowthValue = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_SArmorGrowthValue")));

	TB_SHealth = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_SHealth")));
	TB_SHealthGrowthValue = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_SHealthGrowthValue")));

	TB_SMana = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_SMana")));
	TB_SManaGrowthValue = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_SManaGrowthValue")));

	TB_SMoveSpeed = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_SMoveSpeed")));
	TB_SMoveSpeedGrowthValue = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_SMoveSpeedGrowthValue")));

	TB_SAttackSpeed = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_SAttackSpeed")));
	TB_SAttackSpeedGrowthValue = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_SAttackSpeedGrowthValue")));

	TB_SCriticalPercent = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_SCriticalPercent")));
	TB_SCriticalPercentGrowthValue = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_SCriticalPercentGrowthValue")));
	
	TB_SCriticalDamage = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_SCriticalDamage")));
	TB_SCriticalDamageGrowthValue = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_SCriticalDamageGrowthValue")));


	mTextureRightArrow = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("Texture2D'/Game/GameContent/GUI/Character_Profile_inventory/T_RigthArrow.T_RigthArrow'")));
	mTextureLeftArrow = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("Texture2D'/Game/GameContent/GUI/Character_Profile_inventory/T_LeftArrow.T_LeftArrow'")));
	
	StatusCanvas->SetVisibility(ESlateVisibility::Hidden);
}

FReply UUWEquipmentWindow::NativeOnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	Super::NativeOnMouseButtonDown(MyGeometry,MouseEvent);

	return FReply::Handled();
}

bool UUWEquipmentWindow::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	UDragDropOperation* Operation = Cast<UDragDropOperation>(InOperation);
	UItemObjectData* ItemData = Cast<UItemObjectData>(Operation->Payload);

	//인벤토리로 돌아감
	if (ItemData->IsValid())
	{
		FTile tile;
		tile.X = ItemData->position_x;
		tile.Y = ItemData->position_y;
		
		mInvenComponent->AddItemAt(ItemData, mInvenComponent->TileToIndex(tile));

		mInvenComponent->SetInventoryPacket(ItemData, EInventoryType::Update);
	}
	return false;
}

void UUWEquipmentWindow::Init(UACInventoryComponent* InvenComponent)
{
	mInvenComponent = InvenComponent;
}

void UUWEquipmentWindow::OpenStatus()
{
	if (StatusCanvas->IsVisible())
	{
		StatusCanvas->SetVisibility(ESlateVisibility::Hidden);
		StateButtonIcon->SetBrushFromTexture(mTextureLeftArrow);
	}
	else
	{
		StatusCanvas->SetVisibility(ESlateVisibility::Visible);
		StateButtonIcon->SetBrushFromTexture(mTextureRightArrow);
	}
}
