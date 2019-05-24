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

protected:

	virtual void BeginPlay() override;

public:

	UFUNCTION( BlueprintCallable )
	AItemDefinitionList* GetItemDefinitionList();

protected:

	/** This class is used to spawn the Item Definitino List. */
	UPROPERTY( EditDefaultsOnly )
	TSubclassOf<AItemDefinitionList> ItemDefinitionListClass;

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
