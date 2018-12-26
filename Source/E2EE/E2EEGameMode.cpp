// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "E2EEGameMode.h"

#include "PlayerView.h"

#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"

AE2EEGameMode::AE2EEGameMode()
{
	DefaultPawnClass = APlayerView::StaticClass();



}

void AE2EEGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Enable mouse.
	APlayerController* PlayerCtrl = GetWorld()->GetFirstPlayerController();
	PlayerCtrl->bShowMouseCursor = true;
	PlayerCtrl->bEnableClickEvents = true;
	PlayerCtrl->bEnableMouseOverEvents = true;
}
