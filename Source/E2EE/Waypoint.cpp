// Fill out your copyright notice in the Description page of Project Settings.

#include "Waypoint.h"
#include "E2EECharacter.h"
#include "Messenger.h"

#include "Runtime/Engine/Classes/Components/BoxComponent.h"

AWaypoint::AWaypoint()
{
	// Setup TriggerBox.

	TriggerBox = CreateDefaultSubobject<UBoxComponent>( TEXT( "Trigger Box" ) );
	TriggerBox->SetupAttachment( RootComponent );

	TriggerBox->OnComponentBeginOverlap.AddDynamic( this, &AWaypoint::HandleOnBoxBeginOverlap );
	TriggerBox->OnComponentEndOverlap.AddDynamic( this, &AWaypoint::HandleOnBoxEndOverlap );

	// Setup DefaultItemDropOff.

	DefaultItemDropOff = CreateDefaultSubobject<USceneComponent>( TEXT( "Default Item Drop Off" ) );
	DefaultItemDropOff->SetupAttachment( RootComponent );
}

FVector AWaypoint::GetDefaultItemDropOffLocation()
{
	return DefaultItemDropOff->GetComponentLocation();
}

TArray<ACharacter*> AWaypoint::GetOccupants()
{
	return Occupants;
}

void AWaypoint::HandleOnBoxBeginOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult )
{
	ACharacter* Occupant = Cast<ACharacter>( OtherActor );
	if ( Occupant )
	{
		Occupants.Add( Occupant );

		if ( Cast<ABasicCharacter>( Occupant ) )
		{
			Cast<ABasicCharacter>( Occupant )->SetCurrentWaypoint( this );
		}
		else if ( Cast<AMessenger>( Occupant ) )
		{
			Cast<AMessenger>( Occupant )->SetCurrentWaypoint( this );
		}
	}
}

void AWaypoint::HandleOnBoxEndOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex )
{
	ACharacter* Occupant = Cast<ACharacter>( OtherActor );
	if ( Occupant )
	{
		Occupants.RemoveSwap( Occupant );

		if ( Cast<ABasicCharacter>( Occupant ) )
		{
			Cast<ABasicCharacter>( Occupant )->SetCurrentWaypoint( nullptr );
		}
		else if ( Cast<AMessenger>( Occupant ) )
		{
			Cast<AMessenger>( Occupant )->SetCurrentWaypoint( nullptr );
		}
	}
}
