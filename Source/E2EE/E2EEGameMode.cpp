// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "E2EEGameMode.h"

#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"

AE2EEGameMode::AE2EEGameMode()
{
	// Set default pawn.
	//static ConstructorHelpers::FClassFinder<APawn> ThirdPersonCharacterAssetFinder( TEXT( "/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter" ) );
	//DefaultPawnClass = ThirdPersonCharacterAssetFinder.Class;
	DefaultPawnClass = nullptr;
}

void AE2EEGameMode::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerCtrl = GetWorld()->GetFirstPlayerController();

	// Enable mouse.
	PlayerCtrl->bShowMouseCursor = true;
	PlayerCtrl->bEnableClickEvents = true;
	PlayerCtrl->bEnableMouseOverEvents = true;

	// Don't switch camera when possessing.
	PlayerCtrl->bAutoManageActiveCameraTarget = false;


}
