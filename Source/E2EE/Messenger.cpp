// Fill out your copyright notice in the Description page of Project Settings.

#include "Messenger.h"
#include "MyPlayerController.h"
#include "E2EECharacter.h"
#include "Waypoint.h"

#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "Runtime/Engine/Classes/AI/NavigationSystemBase.h"
#include "Runtime/AIModule/Classes/AIController.h"

AMessenger::AMessenger()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMessenger::BeginPlay()
{
	Super::BeginPlay();

	MyAIController = GetController<AAIController>();
}

void AMessenger::SetupPlayerInputComponent( UInputComponent* PlayerInputComponent )
{
	Super::SetupPlayerInputComponent( PlayerInputComponent );
}

void AMessenger::Summon()
{
	UE_LOG( LogTemp, Display, TEXT( "Messenger is being summoned." ) );

	AWaypoint* TargetWaypoint = nullptr;

	// Get target waypoint.
	// Don't move if there's no active character.
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>( GetWorld()->GetFirstPlayerController() );
	AE2EECharacter* ActiveCharacter = PlayerController->GetActiveCharacter();
	if ( ActiveCharacter )
	{
		if ( ActiveCharacter->GetUsername() == "Alice" ) { TargetWaypoint = Waypoint_Alice; }
		else if ( ActiveCharacter->GetUsername() == "Bob" ) { TargetWaypoint = Waypoint_Bob; }
		else { UE_LOG( LogTemp, Error, TEXT( "Messenger: Active character's name is an unexpected string." ) ); }
	}
	else
	{
		return;
	}

	MyAIController->MoveToActor( TargetWaypoint );
}

AWaypoint* AMessenger::GetCurrentWaypoint()
{
	return CurrentWaypoint;
}

void AMessenger::SetCurrentWaypoint( AWaypoint* TheWaypoint )
{
	CurrentWaypoint = TheWaypoint;
}
