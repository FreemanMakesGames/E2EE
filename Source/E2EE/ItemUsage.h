#pragma once

#include "ItemUsage.generated.h"

UENUM( BlueprintType )
enum class EItemUsage : uint8
{
	// General
	Destroy			UMETA( DisplayName = "Destroy" ),
	Drop			UMETA( DisplayName = "Drop" ),
	Duplicate		UMETA( DisplayName = "Duplicate" ),

	// Combination
	Lock			UMETA( DisplayName = "Lock" ),
	Unlock			UMETA( DisplayName = "Unlock" ),
	Contain			UMETA( DisplayName = "Contain" ),

	Open			UMETA( DisplayName = "Open" ),

	Read			UMETA( DisplayName = "Read" )
};
