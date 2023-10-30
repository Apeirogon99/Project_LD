// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Struct/Game/GameDatas.h"
#include "Struct/Game/CharacterDatas.h"
#include "Struct/Game/CharacterStatusData.h"
#include <Game/PS_Game.h>
#include "UWInventory.generated.h"

/**
 * 
 */
class UBorder;
class UBackgroundBlur;
class UTextBlock;
class UButton;
class UImage;
class UCanvasPanel;
class UACInventoryComponent;

UCLASS()
class PROJECT_LD_API UUWInventory : public UUserWidget
{
	GENERATED_BODY()
		
public:
	UPROPERTY()
	UWidget* mGridInventory;

	UPROPERTY()
	UWidget* mInvenFrame;

	UPROPERTY()
	UWidget* mEquipHelmet;

	UPROPERTY()
	UWidget* mEquipShoulders;

	UPROPERTY()
	UWidget* mEquipChest;

	UPROPERTY()
	UWidget* mEquipBracers;

	UPROPERTY()
	UWidget* mEquipHands;

	UPROPERTY()
	UWidget* mEquipPants;

	UPROPERTY()
	UWidget* mEquipBoots;

	UPROPERTY()
	UWidget* mEquipLeftWeapon;
	
	UPROPERTY()
	UWidget* mEquipRightWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components | Main | Money", meta = (BindWidget))
	UTextBlock* TB_Money;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components | Detail | Canvas", meta = (BindWidget))
	UCanvasPanel* DetailCanvas;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components | Border", meta = (BindWidget))
	UBorder* BackgroundBorder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components | Main | Button", meta = (BindWidget))
	UButton* Btn_CloseInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components | Main | Button", meta = (BindWidget))
	UButton* Btn_DetailStatus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components | Main | TextBlock", meta = (BindWidget))
	UTextBlock* TB_Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components | Main | TextBlock", meta = (BindWidget))
	UTextBlock* TB_CharacterName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components | Main | TextBlock", meta = (BindWidget))
	UTextBlock* TB_Power;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components | Main | TextBlock", meta = (BindWidget))
	UTextBlock* TB_Armor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components | Main | TextBlock", meta = (BindWidget))
	UTextBlock* TB_Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components | Main | TextBlock", meta = (BindWidget))
	UTextBlock* TB_Mana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components | Main | Image", meta = (BindWidget))
	UImage* Img_Power;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components | Main | Image", meta = (BindWidget))
	UImage* Img_Armor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components | Main | Image", meta = (BindWidget))
	UImage* Img_Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components | Main | Image", meta = (BindWidget))
	UImage* Img_Mana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components | Detail | TextBlock | Attack", meta = (BindWidget))
	UTextBlock* TB_DTAttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components | Detail | TextBlock | Attack", meta = (BindWidget))
	UTextBlock* TB_DTAbilityPower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components | Detail | TextBlock | Attack", meta = (BindWidget))
	UTextBlock* TB_DTAttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components | Detail | TextBlock | Attack", meta = (BindWidget))
	UTextBlock* TB_DTCriticalStrikeChance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components | Detail | TextBlock | Attack", meta = (BindWidget))
	UTextBlock* TB_DTCriticalStrikeDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components | Detail | TextBlock | Attack", meta = (BindWidget))
	UTextBlock* TB_DTArmorPenetration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components | Detail | TextBlock | Attack", meta = (BindWidget))
	UTextBlock* TB_DTMagePenetration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components | Detail | TextBlock | Attack", meta = (BindWidget))
	UTextBlock* TB_DTAbilityHaste;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components | Detail | TextBlock | Attack", meta = (BindWidget))
	UTextBlock* TB_DTMovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components | Detail | TextBlock | Attack", meta = (BindWidget))
	UTextBlock* TB_DTRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components | Detail | TextBlock | Defense", meta = (BindWidget))
	UTextBlock* TB_DTArmor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components | Detail | TextBlock | Defense", meta = (BindWidget))
	UTextBlock* TB_DTTenacity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components | Detail | TextBlock | Defense", meta = (BindWidget))
	UTextBlock* TB_DTMagicResistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components | Detail | TextBlock | Defense", meta = (BindWidget))
	UTextBlock* TB_DTSlowResist;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components | Detail | TextBlock | Health", meta = (BindWidget))
	UTextBlock* TB_DTHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components | Detail | TextBlock | Health", meta = (BindWidget))
	UTextBlock* TB_DTHealthReneration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components | Detail | TextBlock | Health", meta = (BindWidget))
	UTextBlock* TB_DTLifeSteal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components | Detail | TextBlock | Health", meta = (BindWidget))
	UTextBlock* TB_DTPhysicalVamp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components | Detail | TextBlock | Health", meta = (BindWidget))
	UTextBlock* TB_DTOmnivamp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components | Detail | TextBlock | Health", meta = (BindWidget))
	UTextBlock* TB_DTHealAndShieldPower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components | Detail | TextBlock | Mana", meta = (BindWidget))
	UTextBlock* TB_DTMana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components | Detail | TextBlock | Mana", meta = (BindWidget))
	UTextBlock* TB_DTManaRegeneration;
	
public:
	FORCEINLINE float												GetTileSize() const							{ return mTileSize; }
	FORCEINLINE UACInventoryComponent*			GetInventoryComponent() const		{ return mInvenComponent; }
	FORCEINLINE UACEquipment*							GetEquipmentComponent() const		{ return mEquipmentComponent; }
	FORCEINLINE APS_Game*									GetPlayerState()	const						{ return mPlayerState; }

public:
	void		SetTileSize(const float TileSize)																			{ mTileSize = TileSize; }
	void		SetInventoryComponent(UACInventoryComponent* InventoryComponent)		{ mInvenComponent = InventoryComponent; }
	void		SetEquipmentComponent(UACEquipment* EquipmentComponent)						{ mEquipmentComponent = EquipmentComponent; }
	void		SetPlayerState(APS_Game* playerstate)																{ mPlayerState = playerstate; }

public:
	UFUNCTION()
	void CloseInventory();

	UFUNCTION()
	void ToggleDetailPanel();

	UFUNCTION()
	void UpdateMoney();

public:
	void InitInventory(UACInventoryComponent* InventoryComponent, float size, UACEquipment* EquipmentComponent);

protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;
	virtual void NativeDestruct() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual bool NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
		
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "default", meta = (AllowPrivateAccess = "true"))
	float mTileSize;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	UACInventoryComponent* mInvenComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment", meta = (AllowPrivateAccess = "true"))
	UACEquipment* mEquipmentComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = "true"))
	APS_Game* mPlayerState;
};