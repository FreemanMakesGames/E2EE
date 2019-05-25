#include "Item.h"

#include "ItemInfo.h"
#include "ItemWidget.h"
#include "DevUtilities.h"

#include "Net/UnrealNetwork.h"

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
