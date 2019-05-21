#include "PickupComponent.h"

#include "BasicPlayerController.h"
#include "BasicCharacter.h"
#include "Inventory.h"
#include "Item.h"
#include "GameUtilities.h"

#include "Engine/Engine.h"
#include "Components/PrimitiveComponent.h"

UPickupComponent::UPickupComponent()
{
	PickupRange = 300.0f;
}

void UPickupComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerItem = Cast<AItem>( GetOwner() );
	if ( !OwnerItem )
	{
		GEngine->AddOnScreenDebugMessage( -1, 100.0f, FColor::Red, TEXT( "PickupComponent is added to a non-Item!" ) );
		return;
	}

	UPrimitiveComponent* OwnerPrimitiveComponent = GetOwner()->FindComponentByClass<UPrimitiveComponent>();
	if ( OwnerPrimitiveComponent )
	{
		OwnerPrimitiveComponent->OnClicked.AddDynamic( this, &UPickupComponent::PickUp );
	}
}

void UPickupComponent::PickUp( UPrimitiveComponent* TouchedComponent, FKey ButtonPressed )
{
	// Get ActiveCharacter and ActiveInventory.
	ABasicCharacter* ActiveCharacter = Cast<ABasicPlayerController>( GetWorld()->GetFirstPlayerController() )->GetActiveCharacter();
	if ( !ActiveCharacter ) { return; }
	UInventory* ActiveInventory = ActiveCharacter->GetInventory();

	// Check if ActiveCharacter is within PickupRange.
	float Distance = FVector::Distance( ActiveCharacter->GetActorLocation(), GetOwner()->GetActorLocation() );
	if ( Distance > PickupRange )
	{
		//UGameUtilities::DisplayNotification( "Too far to pick up this item!" );
		return;
	}

	// Add OwnerItem to ActiveInventory.
	ActiveInventory->AddItem( OwnerItem );

	// TODO: Pickup: Change this to destroy OwnerItem.
	UGameUtilities::DisableActor( OwnerItem );
}
