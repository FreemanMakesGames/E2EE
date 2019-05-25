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

void UItemInfo::SetItemTypeId( int InItemTypeId )
{
	ItemTypeId = InItemTypeId;
}

TArray<EItemUsage> UItemInfo::GetItemUsages()
{
	return ItemUsages;
}

AItem* UItemInfo::SpawnItem( const FTransform& SpawnTransform )
{
	AItem* Item = nullptr;

	UWorld* World = GetWorld();
	if ( World )
	{
		 Item = GetWorld()->SpawnActor<AItem>( ItemClass, SpawnTransform );

		 Item->SetItemInfo( this );
	}
	else
	{
		UDevUtilities::PrintError( "UItemInfo::SpawnItem: World doesn't exist yet!" );
	}

	return Item;
}
