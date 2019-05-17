#include "BasicPlayerController.h"

#include "MPGameMode.h"
#include "BasicCharacter.h"
#include "InventoryMenu.h"
#include "Inventory.h"

#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

ABasicPlayerController::ABasicPlayerController() {}

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

	// Create InventoryMenu.
	if ( InventoryMenuClass )
	{
		InventoryMenu = CreateWidget<UInventoryMenu>( this, InventoryMenuClass );
	}
	else
	{
		UE_LOG( LogTemp, Error, TEXT( "AMyPlayerController's InventoryMenuClass isn't set!" ) );
		return;
	}
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
			UE_LOG( LogTemp, Error, TEXT( "MPGameMode can't be found. Are we in Singleplayer?" ) );
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
		AMPGameMode* MPGameMode = GetWorld()->GetAuthGameMode<AMPGameMode>();

		if ( MPGameMode )
		{
			MPGameMode->ProcessCharacterInteractionRequest( this, TargetCharacter );
		}
		else
		{
			Possess( TargetCharacter );

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

void ABasicPlayerController::ShowInventoryMenu()
{
	if ( ActiveCharacter )
	{
		InventoryMenu->ShowInventory( ActiveCharacter->GetInventory() );
	}
}
