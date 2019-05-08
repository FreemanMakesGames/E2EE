#pragma once

#include "ItemUsage.generated.h"

UENUM( BlueprintType )
enum class EItemUsage : uint8
{
	Destroy			UMETA( DisplayName = "Destroy" ),
	Drop			UMETA( DisplayName = "Drop" )
};
