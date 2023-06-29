#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EnemyStateTypeData.generated.h"

UENUM(BlueprintType)
enum class EEnemyStateType : uint8
{
	None		UMETA(DisPlayNone = "None"),
	Idle			UMETA(DisplayName = "Idle"),
	Chase		UMETA(DisplayName = "Chase"),
	Death		UMETA(DisplayName = "Death"),
	Attack		UMETA(DisplayName = "Attack"),
	Hit			UMETA(DisplayName = "Hit")
};

UCLASS()
class PROJECT_LD_API UEnemyStateTypeData : public UObject
{
	GENERATED_BODY()
};