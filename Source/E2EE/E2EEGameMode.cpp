// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "E2EEGameMode.h"
#include "MyPlayerController.h"

#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"

AE2EEGameMode::AE2EEGameMode()
{
	DefaultPawnClass = nullptr;

	PlayerControllerClass = AMyPlayerController::StaticClass();
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
