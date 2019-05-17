#include "Inventory.h"

#include "DropItemComponent.h"

#include "Item.h"

TArray<AItem*> UInventory::GetItems()
{
	return Items;
}

int UInventory::CountItems()
{
	return Items.Num();
}

void UInventory::AddItem( AItem* ItemToAdd )
{
	Items.Add( ItemToAdd );

	OnItemAdded.Broadcast( ItemToAdd );
}

void UInventory::RemoveItem( AItem* ItemToRemove )
{
	Items.Remove( ItemToRemove );

	OnItemRemoved.Broadcast( ItemToRemove );
}

void UInventory::DropItem( AItem* ItemToDrop )
{
	UDropItemComponent* DropItemComponent = GetOwner()->FindComponentByClass<UDropItemComponent>();

	if ( DropItemComponent )
	{
		DropItemComponent->ServerDropItem( ItemToDrop );
	}
	else
	{
		UE_LOG( LogTemp, Error, TEXT( "The owner of this UInventory doesn't have a UDropItemComponent! Aborted." ) );
		return;
	}

	RemoveItem( ItemToDrop );
}

AItem* UInventory::DuplicateItem( AItem* ItemToDuplicate )
{
	AItem* Clone = ItemToDuplicate->Duplicate();

	if ( Clone )
	{
		AddItem( Clone );
	}
	else
	{
		UE_LOG( LogTemp, Warning, TEXT( "Item duplication failed?!" ) );
	}

	return Clone;
}

void UInventory::CombineItems( TArray<AItem*> SourceItems )
{
	TArray<AItem*> ResultItems = CombineItemsWithItemCombiner( SourceItems );

	if ( ResultItems == SourceItems )
	{
		return;
	}
	else
	{
		for ( AItem* Item : SourceItems )
		{
			RemoveItem( Item );
		}

		for ( AItem* Item : ResultItems )
		{
			AddItem( Item );
		}
	}
}
