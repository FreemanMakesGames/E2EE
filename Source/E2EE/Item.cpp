#include "Item.h"

#include "ItemInfo.h"
#include "ItemWidget.h"
#include "GameUtilities.h"

#include "Net/UnrealNetwork.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	bReplicateMovement = true;
	bAlwaysRelevant = true;
	NetDormancy = ENetDormancy::DORM_Never;
}
