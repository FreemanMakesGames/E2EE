#include "ItemInfo.h"

#include "Item.h"
#include "ItemWidget.h"
#include "DevUtilities.h"

#include "Net/UnrealNetwork.h"

TSubclassOf<AItem> UItemInfo::GetItemClass()
{
	return ItemClass;
}

TSubclassOf<UItemWidget> UItemInfo::GetItemWidgetClass()
{
	return ItemWidgetClass;
}

int UItemInfo::GetItemTypeId()
{
	return ItemTypeId;
}

TArray<EItemUsage> UItemInfo::GetItemUsages()
{
	return ItemUsages;
}

// FIXME: This needs a World passed onto it or something.
AItem* UItemInfo::SpawnItem( const FTransform& SpawnTransform )
{
	AItem* Item = nullptr;

	UWorld* World = GetWorld();
	if ( World )
	{
		 Item = GetWorld()->SpawnActor<AItem>( ItemClass, SpawnTransform );

		 this->Rename( *GetName(), Item );

		 Item->SetItemInfo( this );
	}
	else
	{
		UDevUtilities::PrintError( "UItemInfo::SpawnItem: World doesn't exist yet!" );
	}

	return Item;
}

void UItemInfo::GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );

	DOREPLIFETIME( UItemInfo, ItemUsages );
}
