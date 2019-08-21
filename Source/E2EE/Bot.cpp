// Fill out your copyright notice in the Description page of Project Settings.

#include "Bot.h"
#include "BasicPlayerController.h"
#include "BasicCharacter.h"
#include "Waypoint.h"
#include "DevUtilities.h"

#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "Runtime/Engine/Classes/AI/NavigationSystemBase.h"
#include "Runtime/AIModule/Classes/AIController.h"

ABot::ABot()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->OnClicked.AddDynamic( this, &ABot::OnCapsuleClicked );
}

void ABot::BeginPlay()
{
	Super::BeginPlay();

	AIController = GetController<AAIController>();
}

void ABot::SetupPlayerInputComponent( UInputComponent* PlayerInputComponent )
{
	Super::SetupPlayerInputComponent( PlayerInputComponent );
}

void ABot::OnCapsuleClicked( UPrimitiveComponent* TouchedComponent, FKey ButtonPressed )
{
	Summon();
}

void ABot::Summon()
{
	UDevUtilities::PrintInfo( "Messenger is being summoned." );

	AWaypoint* TargetWaypoint = nullptr;

	ABasicPlayerController* PlayerController = Cast<ABasicPlayerController>( GetWorld()->GetFirstPlayerController() );

	// Get target waypoint.
	// Don't move if there's no active character.
	ABasicCharacter* ActiveCharacter = PlayerController->GetActiveCharacter();
	if ( ActiveCharacter )
	{
		if ( ActiveCharacter->GetUsername() == "Alice" ) { TargetWaypoint = Waypoint_Alice; }
		else if ( ActiveCharacter->GetUsername() == "Bob" ) { TargetWaypoint = Waypoint_Bob; }
		else { UDevUtilities::PrintError( "Messenger: Active character's name is an unexpected string." ); return; }
	}
	else
	{
		PlayerController->DisplayNotification( NSLOCTEXT( "", "", "Select Alice/Bob before you summon the messenger." ) );

		return;
	}

	// Only move if there are dropped items in TargetWaypoint.
	if ( TargetWaypoint->GetDroppedItems().Num() > 0 )
	{
		AIController->MoveToActor( TargetWaypoint );
	}
	else
	{
		PlayerController->DisplayNotification( NSLOCTEXT( "", "", "No item is dropped in the area for the messenger to send." ) );
	}
}

AWaypoint* ABot::GetCurrentWaypoint()
{
	return CurrentWaypoint;
}

void ABot::SetCurrentWaypoint( AWaypoint* TheWaypoint )
{
	CurrentWaypoint = TheWaypoint;
}
