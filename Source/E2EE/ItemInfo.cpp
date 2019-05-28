#include "ItemInfo.h"

#include "Item.h"
#include "ItemWidget.h"
#include "DevUtilities.h"

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

		 Item->SetItemInfo( this );

		 this->Rename( *GetName(), Item );
	}
	else
	{
		UDevUtilities::PrintError( "UItemInfo::SpawnItem: World doesn't exist yet!" );
	}

	return Item;
}
