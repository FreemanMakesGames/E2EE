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
	PickupRange = 3000.0f;
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

	// FIXME: OwnerItem's ItemInfo is null here when client picks up.
	UItemInfo* OwnerItemInfo = OwnerItem->GetItemInfo();
	ActiveInventory->AddItem( OwnerItemInfo );

	OwnerItemInfo->Rename( *OwnerItemInfo->GetName(), GetWorld() );

	OwnerItem->Destroy();
}
