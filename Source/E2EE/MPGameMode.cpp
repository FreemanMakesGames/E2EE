#include "MPGameMode.h"

#include "BasicPlayerController.h"
#include "BasicCharacter.h"

void AMPGameMode::ProcessTeamSelectionRequest( ABasicPlayerController* PlayerCtrl, ETeam Team )
{
	if ( Team == ETeam::AliceAndBob && AliceAndBobCtrl == nullptr )
	{
		AliceAndBobCtrl = PlayerCtrl;

		PlayerCtrl->ClientReceiveTeamSelectionResult( true );
	}
	else if ( Team == ETeam::Messenger && MessengerCtrl == nullptr )
	{
		MessengerCtrl = PlayerCtrl;

		PlayerCtrl->ClientReceiveTeamSelectionResult( true );
	}
	else
	{
		PlayerCtrl->ClientReceiveTeamSelectionResult( false );
	}
}

void AMPGameMode::ProcessCharacterInteractionRequest( ABasicPlayerController* PlayerCtrl, ABasicCharacter* TargetCharacter )
{
	if ( ( PlayerCtrl == AliceAndBobCtrl && TargetCharacter->GetTeam() == ETeam::AliceAndBob ) || ( PlayerCtrl == MessengerCtrl && TargetCharacter->GetTeam() == ETeam::Messenger ) )
	{
		PlayerCtrl->Possess( TargetCharacter );

		PlayerCtrl->ClientReceiveCharacterInteractionResult( true, TargetCharacter );
	}
	else
	{
		PlayerCtrl->ClientReceiveCharacterInteractionResult( false, TargetCharacter );
	}
}
