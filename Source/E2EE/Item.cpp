#include "Item.h"

#include "ItemInfo.h"
#include "ItemWidget.h"
#include "DevUtilities.h"

#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"

AItem::AItem( const FObjectInitializer& ObjectInitializer ) : Super( ObjectInitializer )
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	bReplicateMovement = true;
	bAlwaysRelevant = true;
	NetDormancy = ENetDormancy::DORM_Never;
}

UItemInfo* AItem::GetItemInfo()
{
	return ItemInfo;
}

void AItem::SetItemInfo( UItemInfo* InItemInfo )
{
	if ( !ItemInfo )
	{
		ItemInfo = InItemInfo;
	}
	else
	{
		UDevUtilities::PrintError( "AItem::SetItemInfo: This AItem already has a UItemInfo!" );
	}
}

bool AItem::ReplicateSubobjects( class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags )
{
	bool WroteSomething = Super::ReplicateSubobjects( Channel, Bunch, RepFlags );

	if ( ItemInfo != nullptr )
	{
		WroteSomething |= Channel->ReplicateSubobject( ItemInfo, *Bunch, *RepFlags );
	}

	return WroteSomething;
}

void AItem::GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );

	DOREPLIFETIME( AItem, ItemInfo );
}
