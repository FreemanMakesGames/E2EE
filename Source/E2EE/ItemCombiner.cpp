#include "ItemCombiner.h"

#include "LockItemInfo.h"
#include "KeyItemInfo.h"
#include "ContainerItemInfo.h"
#include "DevUtilities.h"

UItemCombiner::UItemCombiner()
{
	/* All possible combination among Item types */

	FArrayOfItemTypeId LockAndContainer;
	LockAndContainer.ItemTypeIds.Add( 0 );
	LockAndContainer.ItemTypeIds.Add( 2 );
	FunctionMap.Add( LockAndContainer, &UItemCombiner::LockContainer );

	FArrayOfItemTypeId KeyAndContainer;
	KeyAndContainer.ItemTypeIds.Add( 1 );
	KeyAndContainer.ItemTypeIds.Add( 2 );
	FunctionMap.Add( KeyAndContainer, &UItemCombiner::UnlockContainer );

	FunctionMapForWildCards.Add( 2, &UItemCombiner::ContainItem );
}

TArray<UItemInfo*> UItemCombiner::CombineItems(TArray<UItemInfo*> SourceItems)
{
	TArray<UItemInfo*> Results;

	// TODO: Item Combination: There may be a better way to prevent combining an item with itself.
	// Prevent combination with itself.
	if ( SourceItems[0] == SourceItems[1] )
	{
		// TODO: Item Combination: Notify player to select a different item to combine.

		Results.Add( SourceItems[0] );

		return Results;
	}

	// Gather Item Type IDs.
	FArrayOfItemTypeId SourceItemTypeIds;
	for ( int i = 0; i < SourceItems.Num(); i++ )
	{
		int ItemTypeId = SourceItems[i]->GetItemTypeId();

		SourceItemTypeIds.ItemTypeIds.Add( ItemTypeId );
	}

	FCombineFunction* CombineFunctionPointer = FunctionMap.Find( SourceItemTypeIds );
	if ( !CombineFunctionPointer )
	{
		CombineFunctionPointer = FunctionMapForWildCards.Find( SourceItemTypeIds.ItemTypeIds[0] );
	}

	if ( CombineFunctionPointer )
	{
		FCombineFunction CombineFunction = *CombineFunctionPointer;

		Results = ( this->*( CombineFunction ) )( SourceItems );

		return Results;
	}
	else
	{
		return SourceItems;
	}
}

TArray<UItemInfo*> UItemCombiner::LockContainer( TArray<UItemInfo*> SourceItems )
{
	TArray<UItemInfo*> Results;

	ULockItemInfo* Lock = Cast<ULockItemInfo>( SourceItems[0] );
	UContainerItemInfo* Container = Cast<UContainerItemInfo>( SourceItems[1] );

	if ( Lock && Container )
	{
		if ( Container->IsLocked() )
		{
			// TODO: Item Combination: Notify player that the container isn't locked.

			return SourceItems;
		}

		Container->LockUp( Lock );

		Results.Add( Container );

		return Results;
	}
	else
	{
		ensureMsgf( false, TEXT( "Function map is probably setup wrong with Item Type ID" ) );

		return SourceItems;
	}
}

TArray<UItemInfo*> UItemCombiner::UnlockContainer( TArray<UItemInfo*> SourceItems )
{
	TArray<UItemInfo*> Results;

	UKeyItemInfo* Key = Cast<UKeyItemInfo>( SourceItems[0] );
	UContainerItemInfo* Container = Cast<UContainerItemInfo>( SourceItems[1] );

	if ( Key && Container )
	{
		if ( !Container->IsLocked() )
		{
			// TODO: Item Combination: Notify player that the container isn't locked.

			return SourceItems;
		}

		if ( Container->GetLockId() != Key->GetKeyId() )
		{
			// TODO: Item Combination: Notify player that the key doesn't match the lock.

			return SourceItems;
		}

		Container->Unlock();

		Results.Add( Container );

		return Results;
	}
	else
	{
		ensureMsgf( false, TEXT( "Function map is probably setup wrong with Item Type ID" ) );

		return SourceItems;
	}
}

TArray<UItemInfo*> UItemCombiner::ContainItem( TArray<UItemInfo*> SourceItems )
{
	TArray<UItemInfo*> Results;

	UContainerItemInfo* Container = Cast<UContainerItemInfo>( SourceItems[0] );
	UItemInfo* Item = SourceItems[1];

	if ( Cast<UContainerItemInfo>( Item ) )
	{
		// TODO: Item Combination: Notify the player that they can't contain a container.

		return SourceItems;
	}

	if ( Container )
	{
		if ( Container->IsLocked() )
		{
			// TODO: Item Combination: Notify player that the container is locked.

			return SourceItems;
		}

		if ( Container->IsOccupied() )
		{
			// TODO: Item Combination: Notify player that the container is occupied.

			return SourceItems;
		}

		Container->ContainItem( Item );

		Results.Add( Container );

		return Results;
	}
	else
	{
		ensureMsgf( false, TEXT( "Function map is probably setup wrong with Item Type ID" ) );

		return SourceItems;
	}
}
