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

	AActor* TargetWayPoint = nullptr;

	// Get target waypoint.
	// Don't move if there's no active character.
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>( GetWorld()->GetFirstPlayerController() );
	if ( PlayerController )
	{
		AE2EECharacter* ActiveCharacter = PlayerController->GetActiveCharacter();
		if ( ActiveCharacter )
		{
			if ( ActiveCharacter->GetUsername() == "Alice" ) { TargetWayPoint = WayPoint_Alice; }
			else if ( ActiveCharacter->GetUsername() == "Bob" ) { TargetWayPoint = WayPoint_Bob; }
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
	}

	// Move to target waypoint.
	AAIController* MyAIController = GetController<AAIController>();
	if ( MyAIController )
	{
		if ( TargetWayPoint )
		{
			GetController<AAIController>()->MoveToActor( TargetWayPoint );
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
	if ( Cast<ATargetPoint>( OtherActor ) == WayPoint_Alice )
	{
		CurrentWayPoint = WayPoint_Alice;
	}
	else if ( Cast<ATargetPoint>( OtherActor ) == WayPoint_Bob )
	{
		CurrentWayPoint = WayPoint_Bob;
	}
}

// Only issue that may happen is if the two trigger volumes overlap.
void AMessenger::HandleOnCapsuleEndOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex )
{
	if ( Cast<ATargetPoint>( OtherActor ) == WayPoint_Alice || Cast<ATargetPoint>( OtherActor ) == WayPoint_Bob )
	{
		CurrentWayPoint = nullptr;
	}
}

ATargetPoint* AMessenger::GetCurrentWayPoint()
{
	return CurrentWayPoint;
}
