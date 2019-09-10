#include "Waypoint.h"

#include "BasicCharacter.h"
#include "Bot.h"
#include "DropItemComponent.h"

#include "Runtime/Engine/Classes/Components/BoxComponent.h"

AWaypoint::AWaypoint()
{
	// Setup TriggerBox.

	TriggerBox = CreateDefaultSubobject<UBoxComponent>( TEXT( "Trigger Box" ) );
	TriggerBox->SetupAttachment( RootComponent );

	TriggerBox->OnComponentBeginOverlap.AddDynamic( this, &AWaypoint::HandleOnBoxBeginOverlap );
	TriggerBox->OnComponentEndOverlap.AddDynamic( this, &AWaypoint::HandleOnBoxEndOverlap );

	// Setup DefaultItemDropOff.

	DropItemComponent = CreateDefaultSubobject<UDropItemComponent>( TEXT( "Drop Item" ) );
	DropItemComponent->SetupAttachment( RootComponent );
}

TArray<ACharacter*> AWaypoint::GetOccupants()
{
	return Occupants;
}

TArray<AItem*> AWaypoint::GetDroppedItems()
{
	return DroppedItems;
}

void AWaypoint::DropMultipleItems( TArray<UItemInfo*> ItemsToDrop )
{
	DropItemComponent->DropMultipleItems( ItemsToDrop );
}

void AWaypoint::HandleOnBoxBeginOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult )
{
	if ( ACharacter* Occupant = Cast<ACharacter>( OtherActor ) )
	{
		Occupants.Add( Occupant );

		if ( Cast<ABasicCharacter>( Occupant ) )
		{
			Cast<ABasicCharacter>( Occupant )->SetCurrentWaypoint( this );
		}
		else if ( Cast<ABot>( Occupant ) )
		{
			Cast<ABot>( Occupant )->SetCurrentWaypoint( this );
		}
	}
	else if ( AItem* DroppedItem = Cast<AItem>( OtherActor ) )
	{
		DroppedItems.Add( DroppedItem );
	}
}

void AWaypoint::HandleOnBoxEndOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex )
{
	if ( ACharacter* Occupant = Cast<ACharacter>( OtherActor ) )
	{
		Occupants.RemoveSwap( Occupant );

		if ( Cast<ABasicCharacter>( Occupant ) )
		{
			Cast<ABasicCharacter>( Occupant )->SetCurrentWaypoint( nullptr );
		}
		else if ( Cast<ABot>( Occupant ) )
		{
			Cast<ABot>( Occupant )->SetCurrentWaypoint( nullptr );
		}
	}
	else if ( AItem* DroppedItem = Cast<AItem>( OtherActor ) )
	{
		DroppedItems.RemoveSingleSwap( DroppedItem );
	}
}
