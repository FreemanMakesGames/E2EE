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
}

TArray<UItemInfo*> UItemCombiner::CombineItems(TArray<UItemInfo*> SourceItems)
{
	FArrayOfItemTypeId SourceItemTypeIds;
	for ( int i = 0; i < SourceItems.Num(); i++ )
	{
		int ItemTypeId = SourceItems[i]->GetItemTypeId();

		SourceItemTypeIds.ItemTypeIds.Add( ItemTypeId );
	}

	FCombineFunction* CombineFunctionPointer = FunctionMap.Find( SourceItemTypeIds );
	if ( CombineFunctionPointer )
	{
		FCombineFunction CombineFunction = *CombineFunctionPointer;

		return ( this->*( CombineFunction ) )( SourceItems );
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
		if ( !Container->IsLocked() )
		{
			Container->LockUp( Lock );

			Results.Add( Container );

			return Results;
		}
		else
		{
			// TODO: Item Combination: Notify player that the container isn't locked.

			return SourceItems;
		}
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
		if ( Container->IsLocked() )
		{
			if ( Container->GetLockId() == Key->GetKeyId() )
			{
				Container->Unlock();

				Results.Add( Container );

				return Results;
			}
			else
			{
				// TODO: Item Combination: Notify player that the key doesn't match the lock.

				return SourceItems;
			}
		}
		else
		{
			// TODO: Item Combination: Notify player that the container isn't locked.

			return SourceItems;
		}
	}
	else
	{
		ensureMsgf( false, TEXT( "Function map is probably setup wrong with Item Type ID" ) );

		return SourceItems;
	}
}
