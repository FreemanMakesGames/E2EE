// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"
#include "E2EECharacter.h"

#include "UObject/ConstructorHelpers.h"

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
