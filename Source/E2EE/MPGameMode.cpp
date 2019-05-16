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

bool AMPGameMode::ProcessCharacterInteractionRequest( ABasicPlayerController* PlayerCtrl, ABasicCharacter* Character )
{
	if ( ( PlayerCtrl == AliceAndBobCtrl && Character->GetTeam() == ETeam::AliceAndBob ) || ( PlayerCtrl == MessengerCtrl && Character->GetTeam() == ETeam::Messenger ) )
	{
		return true;
	}
	else
	{
		return false;
	}
}
