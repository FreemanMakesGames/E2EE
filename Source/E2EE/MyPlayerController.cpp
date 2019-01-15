// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"
#include "E2EECharacter.h"

#include "UObject/ConstructorHelpers.h"

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindKey( FKey( "Z" ), IE_Released, this, &AMyPlayerController::ZoomIn );
	InputComponent->BindKey( FKey( "Q" ), IE_Released, this, &AMyPlayerController::ZoomOut );
	InputComponent->BindKey( FKey( "Tab" ), IE_Released, this, &AMyPlayerController::DisplayInventory );
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
	Possess( Character );
	SetControlRotation( FVector::ZeroVector.ToOrientationRotator() );

	// Turn on Widget_Selected.
	Character->ToggleWidget( true );
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
	if ( ActiveCharacter && ActiveCharacter->OverviewCamera )
	{
		SetViewTargetWithBlend( ActiveCharacter->OverviewCamera, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic );
	}
}

void AMyPlayerController::DisplayInventory()
{
	UE_LOG( LogTemp, Warning, TEXT( "TAB" ) );
}
