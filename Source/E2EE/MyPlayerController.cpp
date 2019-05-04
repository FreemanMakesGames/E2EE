// Fill out your copyright notice in the Description page of Project Settings.

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

	InputComponent->BindKey( FKey( "Z" ), IE_Released, this, &AMyPlayerController::ZoomIn );
	InputComponent->BindKey( FKey( "Q" ), IE_Released, this, &AMyPlayerController::ZoomOut );
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Set Camera_Overview.
	TArray<AActor*> AllCameraOverviews;
	UGameplayStatics::GetAllActorsWithTag( GetWorld(), FName( TEXT( "Camera.Overview" ) ), AllCameraOverviews );
	Camera_Overview = AllCameraOverviews[0];

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

	// Set InventoryMenu's Inventory.
	TArray<UInventory*> Inventories;
	ActiveCharacter->GetComponents<UInventory>( Inventories );
	InventoryMenu->SetInventory( Inventories[0] );
}

void AMyPlayerController::ShowInventoryMenu()
{
	InventoryMenu->AddToViewport();
}

void AMyPlayerController::ZoomIn()
{
	if ( ActiveCharacter && ActiveCharacter->MyCamera )
	{
		SetViewTargetWithBlend( ActiveCharacter->MyCamera, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic );
	}
}

void AMyPlayerController::ZoomOut()
{
	if ( Camera_Overview )
	{
		SetViewTargetWithBlend( Camera_Overview, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic );
	}
}

/*void AMyPlayerController::ToggleInventory()
{
	// Errors.
	if ( !InventoryWidget )
	{
		UE_LOG( LogTemp, Error, TEXT( "InventoryWidget is nullptr. Maybe InventoryWidgetClass isn't assigned." ) );
		return;
	}
	// Skips.
	if ( !ActiveCharacter ) { return; }

	// Toggle the inventory off, if it's on.
	if ( InventoryWidget->IsInViewport() )
	{
		UE_LOG( LogTemp, Warning, TEXT( "Hiding inventory of %s" ), *ActiveCharacter->GetName() );
		InventoryWidget->RemoveFromViewport();
		return;
	}

	UE_LOG( LogTemp, Warning, TEXT( "Showing inventory of %s" ), *ActiveCharacter->GetName() );

	// Display the inventory, if it's off.
	UInventoryComponent* ActiveInventory = Cast<UInventoryComponent>( ActiveCharacter->GetComponentByClass( UInventoryComponent::StaticClass() ) );
	if ( ActiveInventory )
	{
		// Get the tile view.
		UTileView* TileView = Cast<UTileView>( InventoryWidget->GetWidgetFromName( TEXT( "TileView_Items" ) ) );
		if ( TileView )
		{
			InventoryWidget->AddToViewport();

			// Add items to the tile view.
			TArray<FItem> Items = ActiveInventory->GetItems();
			for ( int i = 0; i < Items.Num(); i++ )
			{
				FString ItemName = Items[i].Name;
				UTexture2D* ItemIcon = Items[i].Icon;

				UE_LOG( LogTemp, Warning, TEXT( "%s has item: %s" ), *( ActiveCharacter->GetName() ), *ItemName );

				if ( ItemIcon )
				{
					TileView->AddItem( ItemIcon );
				}
				else
				{
					UE_LOG( LogTemp, Error, TEXT( "%s has no icon." ), *ItemName );
				}
			}
		}
		else
		{
			UE_LOG( LogTemp, Error, TEXT( "InventoryWidget's TileView is nullptr." ) );
			return;
		}
	}
	else
	{
		UE_LOG( LogTemp, Error, TEXT( "%s has no inventory." ), *( ActiveCharacter->GetName() ) );
	}
}*/
