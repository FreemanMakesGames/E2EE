// Fill out your copyright notice in the Description page of Project Settings.

#include "Messenger.h"
#include "MyPlayerController.h"
#include "E2EECharacter.h"

#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "Runtime/Engine/Classes/AI/NavigationSystemBase.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "Runtime/Engine/Classes/Engine/TargetPoint.h"

AMessenger::AMessenger()
{
	PrimaryActorTick.bCanEverTick = true;

	// Setup OnComponentBeginOverlap, and OnComponentEndOverlap event for the capsule component.
	MyCapsuleComponent = Cast<UCapsuleComponent>( GetComponentByClass( UCapsuleComponent::StaticClass() ) );
	MyCapsuleComponent->OnComponentBeginOverlap.AddDynamic( this, &AMessenger::HandleOnCapsuleBeginOverlap );
	MyCapsuleComponent->OnComponentEndOverlap.AddDynamic( this, &AMessenger::HandleOnCapsuleEndOverlap );
}

void AMessenger::BeginPlay()
{
	Super::BeginPlay();
}

void AMessenger::SetupPlayerInputComponent( UInputComponent* PlayerInputComponent )
{
	Super::SetupPlayerInputComponent( PlayerInputComponent );

}

void AMessenger::Summon()
{
	UE_LOG( LogTemp, Display, TEXT( "Messenger is being summoned." ) );

	ATargetPoint* TargetWaypoint = nullptr;

	// Get target waypoint.
	// Don't move if there's no active character.
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>( GetWorld()->GetFirstPlayerController() );
	if ( PlayerController )
	{
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
	}
	else
	{
		UE_LOG( LogTemp, Error, TEXT( "Messenger can't get player controller." ) );

		return;
	}

	MoveToWaypoint( TargetWaypoint );

}

void AMessenger::MoveToWaypoint( ATargetPoint* TargetWaypoint )
{
	AAIController* MyAIController = GetController<AAIController>();
	if ( MyAIController )
	{
		if ( TargetWaypoint )
		{
			GetController<AAIController>()->MoveToActor( TargetWaypoint );
		}
		else
		{
			UE_LOG( LogTemp, Error, TEXT( "Messenger doesn't have a target waypoint." ) );
		}
	}
	else
	{
		UE_LOG( LogTemp, Error, TEXT( "Messenger doesn't have an AI Controller." ) );
	}
}

void AMessenger::HandleOnCapsuleBeginOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult )
{
	if ( Cast<ATargetPoint>( OtherActor ) == Waypoint_Alice )
	{
		CurrentWaypoint = Waypoint_Alice;
	}
	else if ( Cast<ATargetPoint>( OtherActor ) == Waypoint_Bob )
	{
		CurrentWaypoint = Waypoint_Bob;
	}
}

// Only issue that may happen is if the two trigger volumes overlap.
void AMessenger::HandleOnCapsuleEndOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex )
{
	if ( Cast<ATargetPoint>( OtherActor ) == Waypoint_Alice || Cast<ATargetPoint>( OtherActor ) == Waypoint_Bob )
	{
		CurrentWaypoint = nullptr;
	}
}

ATargetPoint* AMessenger::GetCurrentWayPoint()
{
	return CurrentWaypoint;
}
