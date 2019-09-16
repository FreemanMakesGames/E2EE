#include "BasicPlayerController.h"

#include "MPGameMode.h"
#include "BasicCharacter.h"
#include "InventoryMenu.h"
#include "Inventory.h"
#include "Notification.h"
#include "DevUtilities.h"

#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

ABasicPlayerController::ABasicPlayerController( const FObjectInitializer& ObjectInitializer ) : Super( ObjectInitializer )
{
	ClickEventKeys.Add( EKeys::RightMouseButton );
}

void ABasicPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void ABasicPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Don't switch camera when possessing.
	bAutoManageActiveCameraTarget = false;

	// Enable mouse.
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;

	// Create notification widget.
	if ( !NotificationClass ) { ensureAlways( false ); return; }
	Notification = CreateWidget<UNotification>( this, NotificationClass );
	Notification->AddToViewport();
}

ABasicCharacter* ABasicPlayerController::GetActiveCharacter() 
{
	return ActiveCharacter;
}

void ABasicPlayerController::ServerSubmitTeamSelectionRequest_Implementation( ETeam Team )
{
	if ( Role == ROLE_Authority )
	{
		AMPGameMode* MPGameMode = GetWorld()->GetAuthGameMode<AMPGameMode>();

		if ( MPGameMode )
		{
			MPGameMode->ProcessTeamSelectionRequest( this, Team );
		}
		else
		{
			UDevUtilities::PrintError( "MPGameMode can't be found. Are we in Singleplayer?" );
		}
	}
}

bool ABasicPlayerController::ServerSubmitTeamSelectionRequest_Validate( ETeam Team )
{
	return true;
}

void ABasicPlayerController::ClientReceiveTeamSelectionResult_Implementation( bool bSuccessful )
{
	OnTeamSelectionResultReceived.Broadcast( bSuccessful );
}

void ABasicPlayerController::ServerSubmitCharacterInteractionRequest_Implementation( ABasicCharacter* TargetCharacter )
{
	if ( Role == ROLE_Authority )
	{
		if ( AMPGameMode* MPGameMode = GetWorld()->GetAuthGameMode<AMPGameMode>() ) // If multiplayer
		{
			MPGameMode->ProcessCharacterInteractionRequest( this, TargetCharacter );
		}
		else
		{
			//Possess( TargetCharacter );

			ClientReceiveCharacterInteractionResult( true, TargetCharacter );
		}
	}
}

bool ABasicPlayerController::ServerSubmitCharacterInteractionRequest_Validate( ABasicCharacter* Character )
{
	return true;
}

void ABasicPlayerController::ClientReceiveCharacterInteractionResult_Implementation( bool bSuccessful, ABasicCharacter* TargetCharacter )
{
	if ( bSuccessful )
	{
		// Turn off previous character's Widget_Selected.
		// Do nothing if there's no previous character.
		if ( ActiveCharacter )
		{
			ActiveCharacter->ToggleWidget( false );
		}

		// Update ActiveCharacter.
		ActiveCharacter = TargetCharacter;

		SetControlRotation( FVector::ZeroVector.ToOrientationRotator() );

		// Turn on Widget_Selected.
		ActiveCharacter->ToggleWidget( true );
	}
	else
	{

	}
}

void ABasicPlayerController::DisplayNotification( const FText& NotificationText, bool StayInView )
{
	Notification->DisplayNotification( NotificationText, StayInView );
}

void ABasicPlayerController::HideNotification( bool SuddenHide )
{
	Notification->HideNotification( SuddenHide );
}
