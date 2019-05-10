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
		DropItemComponent->DropItem( ItemToDrop );
	}
	else
	{
		UE_LOG( LogTemp, Error, TEXT( "The owner of this UInventory doesn't have a UDropItemComponent! Aborted." ) );
		return;
	}

	RemoveItem( ItemToDrop );
}

void UInventory::CombineItems( TArray<AItem*> Items )
{
	TArray<AItem*> ResultItems = CombineItemsWithItemCombiner( Items );

	if ( ResultItems == Items )
	{
		return;
	}
	else
	{
		for ( AItem* Item : Items )
		{
			RemoveItem( Item );
		}

		for ( AItem* Item : ResultItems )
		{
			AddItem( Item );
		}
	}
}
