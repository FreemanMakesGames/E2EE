#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MPGameMode.generated.h"

class ABasicPlayerController;
class AE2EECharacter;

/**
 * 
 */
UCLASS()
class E2EE_API AMPGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:

	UPROPERTY( VisibleInstanceOnly, BlueprintReadWrite )
	ABasicPlayerController* AliceBobCtrl;

	UPROPERTY( VisibleInstanceOnly, BlueprintReadWrite )
	ABasicPlayerController* MessengerCtrl;

	UPROPERTY( VisibleInstanceOnly, BlueprintReadWrite )
	AE2EECharacter* Alice;

	UPROPERTY( VisibleInstanceOnly, BlueprintReadWrite )
	AE2EECharacter* Bob;

	UPROPERTY( VisibleInstanceOnly, BlueprintReadWrite )
	AE2EECharacter* Messenger;

public:

	UFUNCTION( BlueprintCallable )
	bool ProcessCharacterSelectionRequest( ABasicPlayerController* PlayerCtrl, FString CharacterName );
	
};
