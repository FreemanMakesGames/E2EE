#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "BasicGameState.generated.h"

UCLASS()
class E2EE_API ABasicGameState : public AGameStateBase
{
	GENERATED_BODY()

public:

	UFUNCTION( BlueprintCallable )
	void IncrementUsableKeyPairID();

protected:

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	int NextUsableKeyPairID;
	
};
