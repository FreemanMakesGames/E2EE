// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"
#include "E2EECharacter.h"

#include "UObject/ConstructorHelpers.h"

void AMyPlayerController::SetActiveCharacter( AE2EECharacter* Character )
{
	ActiveCharacter = Character;

	Possess( ActiveCharacter );

	SetControlRotation( FVector::ZeroVector.ToOrientationRotator() );
}
