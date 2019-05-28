#include "Inventory.h"

#include "ItemInfo.h"
#include "ItemCombiner.h"
#include "DropItemComponent.h"
#include "BasicCharacter.h"
#include "DevUtilities.h"

#include "Net/UnrealNetwork.h"

UInventory::UInventory( const FObjectInitializer& ObjectInitializer ) : Super( ObjectInitializer )
{
	bReplicates = true;
}

void UInventory::BeginPlay()
{
	Super::BeginPlay();

	ItemCombiner = NewObject<UItemCombiner>();
}

TArray<UItemInfo*> UInventory::GetItems()
{
	return Items;
}

int UInventory::CountItems()
{
	return Items.Num();
}

void UInventory::AddItem( UItemInfo* ItemToAdd )
{
	ensureAlways( ItemToAdd );

	Items.Add( ItemToAdd );

	OnItemAdded.Broadcast( ItemToAdd );
}

void UInventory::RemoveItem( UItemInfo* ItemToRemove )
{
	Items.Remove( ItemToRemove );

	OnItemRemoved.Broadcast( ItemToRemove );
}

void UInventory::DropItem( UItemInfo* ItemToDrop )
{
	UDropItemComponent* DropItemComponent = GetOwner()->FindComponentByClass<UDropItemComponent>();

	if ( DropItemComponent )
	{
		DropItemComponent->ServerDropItem( ItemToDrop );
	}
	else
	{
		ensureMsgf( false, TEXT( "The owner of this UInventory doesn't have a UDropItemComponent! Aborted." ) );
		return;
	}

	RemoveItem( ItemToDrop );
}

void UInventory::ServerDuplicateItem_Implementation( UItemInfo* TargetItem )
{
	MulticastDuplicateItem( TargetItem );
}

bool UInventory::ServerDuplicateItem_Validate( UItemInfo* TargetItem )
{
	return true;
}

void UInventory::MulticastDuplicateItem_Implementation( UItemInfo* TargetItem )
{
	AddItem( TargetItem->Duplicate() );
}

void UInventory::CombineItems( TArray<UItemInfo*> SourceItems )
{
	TArray<UItemInfo*> ResultItems = ItemCombiner->CombineItems( SourceItems );

	for ( UItemInfo* Item : SourceItems )
	{
		RemoveItem( Item );
	}

	for ( UItemInfo* Item : ResultItems )
	{
		AddItem( Item );
	}
}

void UInventory::GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );

	DOREPLIFETIME( UInventory, Items );
}
