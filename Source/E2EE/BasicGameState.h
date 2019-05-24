#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "BasicGameState.generated.h"

class AItemDefinitionList;

UCLASS()
class E2EE_API ABasicGameState : public AGameStateBase
{
	GENERATED_BODY()

public:

	UFUNCTION( BlueprintCallable )
	AItemDefinitionList* GetItemDefinitionList();

	UFUNCTION( BlueprintCallable )
	void IncrementUsableKeyPairId();

protected:

	UPROPERTY( BlueprintReadOnly )
	AItemDefinitionList* ItemDefinitionList;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	int NextUsableKeyPairId;
	
};
