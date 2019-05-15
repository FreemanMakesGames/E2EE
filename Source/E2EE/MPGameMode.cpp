#include "MPGameMode.h"

bool AMPGameMode::ProcessTeamSelectionRequest( ABasicPlayerController* PlayerCtrl, ETeam Team )
{
	if ( Team == ETeam::AliceAndBob && AliceAndBobCtrl == nullptr )
	{
		AliceAndBobCtrl = PlayerCtrl;
		UE_LOG( LogTemp, Warning, TEXT( "Alice and Bob selection" ) );
		return true;
	}
	else if ( Team == ETeam::Messenger && MessengerCtrl == nullptr )
	{
		MessengerCtrl = PlayerCtrl;
		UE_LOG( LogTemp, Warning, TEXT( "M selection" ) );
		return true;
	}
	UE_LOG( LogTemp, Warning, TEXT( "Selection fails." ) );
	return false;
}
