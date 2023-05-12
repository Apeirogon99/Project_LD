// Fill out your copyright notice in the Description page of Project Settings.


#include "Struct/Game/GameDatas.h"

uint32 GetTypeHash(const FItemData& ItemData)
{
    return FCrc::MemCrc32(&ItemData, sizeof(FItemData));
}
