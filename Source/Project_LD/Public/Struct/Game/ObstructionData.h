#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ObstructionData.generated.h"

/**
 * 
 */
USTRUCT(Atomic, BlueprintType)
struct PROJECT_LD_API FObstructionData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FObstructionData();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
		FString	mName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
		FString mPath;
};
