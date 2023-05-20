// Fill out your copyright notice in the Description page of Project Settings.


#include "Struct/Game/GameDatas.h"

uint32 GetTypeHash(const FItemData& ItemData)
{
    return FCrc::MemCrc32(&ItemData, sizeof(FItemData));
}

UObject* FItemData::ToUObject() const
{
    UItemDataObject* ItemObject = NewObject<UItemDataObject>();//(GetTransientPackage(), NAME_None);
    ItemObject->ItemData = *this;

    return ItemObject;
}

FItemData FItemData::UObjectToFItemData(UObject* Object) const
{
    UItemDataObject* ObjectData = Cast<UItemDataObject>(Object);
    FItemData ItemData;
    if (ObjectData)
    {
        ItemData = ObjectData->ItemData;
    }

    return ItemData;
}

FVector2D UItemDataObject::GetSize()
{
    FVector2D Return;
    if (ItemData.rotation)
    {
        Return.X = ItemData.size_y;
        Return.Y = ItemData.size_x;
        return Return;
    }
    else
    {
        Return.X = ItemData.size_x;
        Return.Y = ItemData.size_y;
        return Return;
    }
    return Return;
}

void UItemDataObject::Rotate()
{
    if (ItemData.rotation)
    {
        ItemData.rotation = 0;
    }
    else
    {
        ItemData.rotation = 1;
    }
}
