#include "MPGameMode.h"

#include "BasicPlayerController.h"

void AMPGameMode::ProcessTeamSelectionRequest( ABasicPlayerController* PlayerCtrl, ETeam Team )
{
	if ( Team == ETeam::AliceAndBob && AliceAndBobCtrl == nullptr )
	{
		AliceAndBobCtrl = PlayerCtrl;

		PlayerCtrl->ClientReceiveTeamSelectionResult( true );

		return;
	}
	else if ( Team == ETeam::Messenger && MessengerCtrl == nullptr )
	{
		MessengerCtrl = PlayerCtrl;

		PlayerCtrl->ClientReceiveTeamSelectionResult( true );

		return;
	}

	PlayerCtrl->ClientReceiveTeamSelectionResult( false );
}
