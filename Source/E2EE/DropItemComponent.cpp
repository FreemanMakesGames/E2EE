#include "DropItemComponent.h"

#include "Item.h"
#include "ItemInfo.h"
#include "BasicGameState.h"
#include "DevUtilities.h"

#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"

UDropItemComponent::UDropItemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UDropItemComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UDropItemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UDropItemComponent::ServerDropItem_Implementation( UItemInfo* ItemToDrop )
{
	if ( !ItemToDrop )
	{
		ensureAlwaysMsgf( false, TEXT( "Server is dropping a null AItem!" ) );
		return;
	}

	ItemToDrop->SpawnItem( GetComponentTransform() );
}

bool UDropItemComponent::ServerDropItem_Validate( UItemInfo* ItemToDrop )
{
	return true;
}

void UDropItemComponent::DropMultipleItems( TArray<UItemInfo*> ItemsToDrop )
{
	FTransform SpawnTransform = GetComponentTransform();

	for ( int i = 0; i < ItemsToDrop.Num(); i++ )
	{
		if ( !ItemsToDrop[i] )
		{
			ensureAlwaysMsgf( false, TEXT( "Server is dropping a null AItem!" ) );
			return;
		}

		SpawnTransform.SetLocation( SpawnTransform.GetLocation() + FVector( 0, 0, SpawnCollisionPreventionStep * i ) );

		ItemsToDrop[i]->SpawnItem( SpawnTransform );
	}
}
