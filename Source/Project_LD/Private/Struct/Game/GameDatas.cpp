// Fill out your copyright notice in the Description page of Project Settings.


#include "Struct/Game/GameDatas.h"

void UItemObjectData::Rotate()
{
    if (rotation)
    {
        rotation = 0;
    }
    else
    {
        rotation = 1;
    }
}

bool UItemObjectData::IsValid()
{
    if (ItemData.category_id == 0)
        return false;
    if (ItemData.size_x == 0)
        return false;
    if (ItemData.size_y == 0)
        return false;
    return true;
}

FVector2D UItemObjectData::GetSize() const
{
    FVector2D Return;
    if (rotation)
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

void UItemObjectData::SettingObjectData(FItemData OtheritemData)
{
   this->ItemData = OtheritemData;
}

void UItemObjectData::Clear()
{
    ItemData.Clear();
    position_x = -1;
    position_y = -1;
    rotation = 0;
}
