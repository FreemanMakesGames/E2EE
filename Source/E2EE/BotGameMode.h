#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BotGameMode.generated.h"

class UStoryDisplay;

/**
 * 
 */
UCLASS()
class E2EE_API ABotGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
	
public:

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable )
	void ReadMessage( AActor* Reader );

protected:

	UPROPERTY( EditDefaultsOnly )
	TSubclassOf<UStoryDisplay> StoryDisplayClass;

	UPROPERTY( BlueprintReadOnly )
	UStoryDisplay* StoryDisplay;

protected:

	UFUNCTION( BlueprintCallable )
	void EndGame( bool PlayerWins );

	UFUNCTION()
	void GoBackToHomeMenu();

};
