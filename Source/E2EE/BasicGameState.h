#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "BasicGameState.generated.h"

class AItemDefinitionList;
class ULockItemInfo;
class UKeyItemInfo;

UCLASS()
class E2EE_API ABasicGameState : public AGameStateBase
{
	GENERATED_BODY()

protected:

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	int NextUsableKeyPairId;

public:

	UFUNCTION( BlueprintCallable )
	void SetIdForKeyPair( ULockItemInfo* InLock, UKeyItemInfo* InKey );

protected:

	UFUNCTION( BlueprintCallable )
	void IncrementUsableKeyPairId();
	
};
