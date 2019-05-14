#include "MyPlayerController.h"
#include "E2EECharacter.h"
#include "InventoryMenu.h"
#include "Inventory.h"

#include "UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/TileView.h"
#include "Runtime/UMG/Public/Components/GridPanel.h"

AMyPlayerController::AMyPlayerController() {}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void AMyPlayerController::BeginPlay()
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

AE2EECharacter* AMyPlayerController::GetActiveCharacter() 
{
	return ActiveCharacter;
}

void AMyPlayerController::SetActiveCharacter( AE2EECharacter* Character )
{
	// Turn off previous character's Widget_Selected.
	// Do nothing if there's no previous character.
	if ( ActiveCharacter )
	{
		ActiveCharacter->ToggleWidget( false );
	}

	// Update ActiveCharacter.
	ActiveCharacter = Character;

	// Possess and adjust rotation.
	Possess( ActiveCharacter );
	SetControlRotation( FVector::ZeroVector.ToOrientationRotator() );

	// Turn on Widget_Selected.
	ActiveCharacter->ToggleWidget( true );
}

void AMyPlayerController::ShowInventoryMenu( UInventory* Inventory )
{
	InventoryMenu->ShowInventory( Inventory );
}
