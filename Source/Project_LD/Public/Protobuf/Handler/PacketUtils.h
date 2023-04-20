// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <Struct/Game/CharacterDatas.h>
#include "PacketUtils.generated.h"


/**
 * 
 */
UCLASS()
class PROJECT_LD_API UPacketUtils : public UObject
{
	GENERATED_BODY()
	
public:
	static const Protocol::ECharacterClass			ConvertToPClass(const ECharacterClass& inClass);
	static const ECharacterClass					ConvertToUClass(const Protocol::ECharacterClass& inClass);

	static const Protocol::ERace					ConvertToPRace(const ECharacterRace& inRace);
	static const ECharacterRace						ConvertToURace(const Protocol::ERace& inRace);

	static const Protocol::SCharacterAppearance		ConvertToPAppearance(const FCharacterAppearance& inAppearance);
	static const Protocol::SCharacterEqipment		ConvertToPEqipment(const FCharacterEquipment& inEquipment);
	static const Protocol::SCharacterData			ConvertToPData(const FCharacterData& inData);
};
