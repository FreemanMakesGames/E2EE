#include "Inventory.h"

#include "Item.h"
#include "DropItemComponent.h"
#include "BasicCharacter.h"

#include "Net/UnrealNetwork.h"

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
	TempNewItem = ItemToAdd;

	Items.Add( ItemToAdd );

	OnItemAdded.Broadcast( ItemToAdd );
}

void UInventory::OnRep_Items()
{
	OnItemAdded.Broadcast( TempNewItem );
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

void UInventory::ServerDuplicateItem_Implementation( AItem* ItemToDuplicate )
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
}

bool UInventory::ServerDuplicateItem_Validate( AItem* ItemToDuplicate )
{
	return true;
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

void UInventory::GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );

	DOREPLIFETIME( UInventory, Items );
}
