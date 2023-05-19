// Fill out your copyright notice in the Description page of Project Settings.


#include "Struct/Game/GameDatas.h"

uint32 GetTypeHash(const FItemData& ItemData)
{
    return FCrc::MemCrc32(&ItemData, sizeof(FItemData));
}

/*
UObject* FItemData::ToUObject() const
{
    FItemData* ItemData = NewObject<FItemData>(GetTransientPackage(), NAME_None);
    ItemData->category_id = category_id;
    ItemData->character_class_id = character_class_id;
    ItemData->race_id = race_id;
    ItemData->tier_id = tier_id;
    ItemData->name = name;
    ItemData->position_x = position_x;
    ItemData->position_y = position_y;
    ItemData->description = description;
    ItemData->cost = cost;
    ItemData->level = level;
    ItemData->rate = rate;
    ItemData->size_x = size_x;
    ItemData->size_y = size_y;
    ItemData->rotation = rotation;
    ItemData->icon = icon;
    ItemData->mesh = mesh;

    return ItemData;
}
*/