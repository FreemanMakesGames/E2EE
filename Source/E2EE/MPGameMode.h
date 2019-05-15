#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MPGameMode.generated.h"

class AMyPlayerController;
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
	AMyPlayerController* AliceBobCtrl;

	UPROPERTY( VisibleInstanceOnly, BlueprintReadWrite )
	AMyPlayerController* MessengerCtrl;

	UPROPERTY( VisibleInstanceOnly, BlueprintReadWrite )
	AE2EECharacter* Alice;

	UPROPERTY( VisibleInstanceOnly, BlueprintReadWrite )
	AE2EECharacter* Bob;

	UPROPERTY( VisibleInstanceOnly, BlueprintReadWrite )
	AE2EECharacter* Messenger;

public:

	UFUNCTION( BlueprintCallable )
	bool ProcessCharacterSelectionRequest( AMyPlayerController* PlayerCtrl, FString CharacterName );
	
};
