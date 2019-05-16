#pragma once

#include "Team.generated.h"

UENUM( BlueprintType )
enum class ETeam : uint8
{
	None				UMETA( DisplayName = "None" ),

	AliceAndBob			UMETA( DisplayName = "Alice And Bob" ),
	Messenger			UMETA( DisplayName = "Messenger" )
};
