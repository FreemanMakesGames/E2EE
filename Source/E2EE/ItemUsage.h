#pragma once

#include "ItemUsage.generated.h"

UENUM( BlueprintType )
enum class EItemUsage : uint8
{
	// General
	Destroy			UMETA( DisplayName = "Destroy" ),
	Drop			UMETA( DisplayName = "Drop" ),

	Lock			UMETA( DisplayName = "Lock" ),
	Unlock			UMETA( DisplayName = "Unlock" ),
	Open			UMETA( DisplayName = "Open" ),
	Contain			UMETA( DisplayName = "Contain" )
};
