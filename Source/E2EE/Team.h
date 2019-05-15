#pragma once

#include "Team.generated.h"

UENUM( BlueprintType )
enum class ETeam : uint8
{
	AliceAndBob			UMETA( DisplayName = "Alice And Bob" ),
	Messenger			UMETA( DisplayName = "Messenger" ),

	None				UMETA( DisplayName = "None" )
};
