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

void AItem::BeginPlay()
{
	Super::BeginPlay();
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

TArray<EItemUsage> AItem::GetItemUsages()
{
	return ItemUsages;
}
