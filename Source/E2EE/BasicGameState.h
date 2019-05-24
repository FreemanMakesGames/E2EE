#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "BasicGameState.generated.h"

class AItemDefinitionList;
class ALock;
class AKeyItem;

UCLASS()
class E2EE_API ABasicGameState : public AGameStateBase
{
	GENERATED_BODY()

public:

	UFUNCTION( BlueprintCallable )
	AItemDefinitionList* GetItemDefinitionList();

protected:

	UPROPERTY( BlueprintReadOnly )
	AItemDefinitionList* ItemDefinitionList;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	int NextUsableKeyPairId;

public:

	UFUNCTION( BlueprintCallable )
	void SetIdForKeyPair( ALock* InLock, AKeyItem* InKey );

protected:

	UFUNCTION( BlueprintCallable )
	void IncrementUsableKeyPairId();
	
};
