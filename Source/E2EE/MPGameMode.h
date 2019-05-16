#pragma once

#include "Team.h"

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MPGameMode.generated.h"

class ABasicPlayerController;
class ABasicCharacter;

/**
 * 
 */
UCLASS()
class E2EE_API AMPGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:

	UPROPERTY( VisibleInstanceOnly, BlueprintReadWrite )
	ABasicPlayerController* AliceAndBobCtrl;

	UPROPERTY( VisibleInstanceOnly, BlueprintReadWrite )
	ABasicPlayerController* MessengerCtrl;

	UPROPERTY( VisibleInstanceOnly, BlueprintReadWrite )
	ABasicCharacter* Alice;

	UPROPERTY( VisibleInstanceOnly, BlueprintReadWrite )
	ABasicCharacter* Bob;

	UPROPERTY( VisibleInstanceOnly, BlueprintReadWrite )
	ABasicCharacter* Messenger;

public:

	UFUNCTION( BlueprintCallable )
	void ProcessTeamSelectionRequest( ABasicPlayerController* PlayerCtrl, ETeam Team );

	UFUNCTION( BlueprintCallable )
	void ProcessCharacterInteractionRequest( ABasicPlayerController* PlayerCtrl, ABasicCharacter* TargetCharacter );
	
};
