#include "PickupComponent.h"

#include "BasicPlayerController.h"
#include "BasicCharacter.h"
#include "Inventory.h"
#include "Item.h"
#include "ItemInfo.h"
#include "GameUtilities.h"
#include "DevUtilities.h"

#include "Engine/Engine.h"
#include "Components/PrimitiveComponent.h"

UPickupComponent::UPickupComponent()
{
	PickupRange = 300;
}

void UPickupComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerItem = Cast<AItem>( GetOwner() );
	if ( !OwnerItem )
	{
		UDevUtilities::PrintError( TEXT( "PickupComponent is added to a non-Item!" ) );
		return;
	}

	UPrimitiveComponent* OwnerPrimitiveComponent = GetOwner()->FindComponentByClass<UPrimitiveComponent>();
	if ( OwnerPrimitiveComponent )
	{
		OwnerPrimitiveComponent->OnClicked.AddDynamic( this, &UPickupComponent::ServerPickUp );
	}
}

void UPickupComponent::ServerPickUp_Implementation( UPrimitiveComponent* TouchedComponent, FKey ButtonPressed )
{
	ABasicCharacter* ActiveCharacter = Cast<ABasicPlayerController>( GetWorld()->GetFirstPlayerController() )->GetActiveCharacter();

	if ( !ActiveCharacter ) { return; }

	UInventory* ActiveInventory = ActiveCharacter->GetInventory();

	// Check if ActiveCharacter is within PickupRange.
	float Distance = FVector::Distance( ActiveCharacter->GetActorLocation(), GetOwner()->GetActorLocation() );
	if ( Distance > PickupRange )
	{
		FFormatNamedArguments Args;
		Args.Add( "OwnerName", ActiveCharacter->GetUsername() );
		FText TooFarNotification = FText::Format( NSLOCTEXT( "PickupComponent", "TooFar", "{OwnerName} is too far from the item." ), Args );

		Cast<ABasicPlayerController>( GetWorld()->GetFirstPlayerController() )->DisplayNotification( TooFarNotification );

		return;
	}

	if ( UItemInfo* OwnerItemInfo = OwnerItem->GetItemInfo() )
	{
		ActiveInventory->AddItem( OwnerItemInfo );

		// FIXME: Should it be ActiveInventory, or ActiveInventory->GetOuter()?
		OwnerItemInfo->Rename( nullptr, ActiveInventory );
	}
	else
	{
		ensureAlways( false );
		return;
	}

	OwnerItem->Destroy();
}

bool UPickupComponent::ServerPickUp_Validate( UPrimitiveComponent* TouchedComponent, FKey ButtonPressed )
{
	return true;
}
