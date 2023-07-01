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
    if (ObjectID == 0)
        return false;
    if (ItemData.GetCategoryID() == 0)
        return false;
    if (ItemData.GetSizeX() == 0)
        return false;
    if (ItemData.GetSizeY() == 0)
        return false;
    return true;
}

FVector2D UItemObjectData::GetSize() const
{
    FVector2D Return;
    if (rotation)
    {
        Return.X = ItemData.GetSizeY();
        Return.Y = ItemData.GetSizeX();
        return Return;
    }
    else
    {
        Return.X = ItemData.GetSizeX();
        Return.Y = ItemData.GetSizeY();
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
    position_x = 0;
    position_y = 0;
    rotation = 0;
}
