#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BotGameMode.generated.h"

/**
 * 
 */
UCLASS()
class E2EE_API ABotGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable )
	void ReadMessage( AActor* Reader );

};
