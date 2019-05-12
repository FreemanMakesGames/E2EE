// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "E2EEGameMode.h"
#include "E2EEGameStateBase.h"
#include "MyPlayerController.h"

#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"

AE2EEGameMode::AE2EEGameMode()
{
	// No default pawn.
	DefaultPawnClass = nullptr;

	// Custom game state
	static ConstructorHelpers::FClassFinder<AE2EEGameStateBase> GameStateBaseClassFinder( TEXT( "/Game/Gameplay/BP_GameStateBase" ) );
	GameStateClass = GameStateBaseClassFinder.Class;

	// Player controller is the blueprint extension of AMyPlayerController.
	static ConstructorHelpers::FClassFinder<AMyPlayerController> PlayerControllerClassFinder( TEXT( "/Game/Gameplay/BP_MyPlayerController" ) );
	PlayerControllerClass = PlayerControllerClassFinder.Class;
}

void AE2EEGameMode::BeginPlay()
{
	Super::BeginPlay();
}
