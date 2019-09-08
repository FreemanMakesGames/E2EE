#include "ItemCombiner.h"

#include "LockItemInfo.h"
#include "KeyItemInfo.h"
#include "ContainerItemInfo.h"
#include "BasicPlayerController.h"
#include "DevUtilities.h"

#include "Engine/World.h"

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

void UItemCombiner::SetPlayerController( ABasicPlayerController* InPlayerController )
{
	PlayerController = InPlayerController;
}

FItemCombinationResult UItemCombiner::CombineItems(TArray<UItemInfo*> SourceItems)
{
	FItemCombinationResult Result;

	// TODO: Item Combination: There may be a better way to prevent combining an item with itself.
	// Prevent combination with itself.
	if ( SourceItems[0] == SourceItems[1] )
	{
		PlayerController->DisplayNotification( NSLOCTEXT( "", "", "You can't combine an item with itself!" ) );

		return Result; // Empty unsuccessful result
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

		Result = ( this->*( CombineFunction ) )( SourceItems );

		return Result; // Result depends on the combination function.
	}
	else
	{
		PlayerController->DisplayNotification( NSLOCTEXT( "", "", "These items can't be combined." ) );

		return Result; // Empty unsuccessful result
	}
}

FItemCombinationResult UItemCombiner::LockContainer( TArray<UItemInfo*> SourceItems )
{
	FItemCombinationResult Result;

	ULockItemInfo* Lock = Cast<ULockItemInfo>( SourceItems[0] );
	UContainerItemInfo* Container = Cast<UContainerItemInfo>( SourceItems[1] );

	if ( Lock && Container )
	{
		if ( Container->IsLocked() )
		{
			FFormatNamedArguments Args;
			Args.Add( "Lock ID", FText::FromString( Container->GetLockId() ) );
			PlayerController->DisplayNotification( FText::Format( NSLOCTEXT( "", "", "The container is already locked by lock '{Lock ID}'!" ), Args ) );

			return Result; // Empty unsuccessful result
		}

		Container->LockUp( Lock );

		Result.ResultItems.Add( Container );
		Result.Successful = true;

		return Result; // Successful result
	}
	else
	{
		ensureMsgf( false, TEXT( "Function map is probably setup wrong with Item Type ID" ) );

		return Result; // Empty unsuccessful result
	}
}

FItemCombinationResult UItemCombiner::UnlockContainer( TArray<UItemInfo*> SourceItems )
{
	FItemCombinationResult Result;

	UKeyItemInfo* Key = Cast<UKeyItemInfo>( SourceItems[0] );
	UContainerItemInfo* Container = Cast<UContainerItemInfo>( SourceItems[1] );

	if ( Key && Container )
	{
		if ( !Container->IsLocked() )
		{
			PlayerController->DisplayNotification( NSLOCTEXT( "", "", "The container isn't locked!" ) );

			return Result; // Empty unsuccessful result
		}

		FString LockId = Container->GetLockId();
		FString KeyId = Key->GetKeyId();

		if ( LockId != KeyId )
		{
			FFormatNamedArguments Args;
			Args.Add( "Lock ID", FText::FromString( LockId ) );
			Args.Add( "Key ID", FText::FromString( KeyId ) );
			PlayerController->DisplayNotification( FText::Format( NSLOCTEXT( "", "", "The container is locked with lock '{Lock ID}', but the key is '{Key ID}'." ), Args ) );

			return Result; // Empty unsuccessful result
		}

		Result.ResultItems.Add( Container->GetLock() );

		Container->Unlock();
		
		Result.ResultItems.Add( Key );
		Result.ResultItems.Add( Container );
		Result.Successful = true;

		return Result; // Successful result
	}
	else
	{
		ensureMsgf( false, TEXT( "Function map is probably setup wrong with Item Type ID" ) );

		return Result; // Empty unsuccessful result
	}
}

FItemCombinationResult UItemCombiner::ContainItem( TArray<UItemInfo*> SourceItems )
{
	FItemCombinationResult Result;

	UContainerItemInfo* Container = Cast<UContainerItemInfo>( SourceItems[0] );
	UItemInfo* Item = SourceItems[1];

	if ( Cast<UContainerItemInfo>( Item ) )
	{
		PlayerController->DisplayNotification( NSLOCTEXT( "", "", "Putting a container into another container isn't allowed!" ) );

		return Result; // Empty unsuccessful result
	}

	if ( Container )
	{
		if ( Container->IsLocked() )
		{
			FFormatNamedArguments Args;
			Args.Add( "Lock ID", FText::FromString( Container->GetLockId() ) );
			PlayerController->DisplayNotification( FText::Format( NSLOCTEXT( "", "", "The container is locked by lock '{Lock ID}'" ), Args ) );

			return Result; // Empty unsuccessful result
		}

		if ( Container->IsOccupied() )
		{
			PlayerController->DisplayNotification( NSLOCTEXT( "", "", "The container is occupied!" ) );

			return Result; // Empty unsuccessful result
		}

		Container->ContainItem( Item );

		Result.ResultItems.Add( Container );
		Result.Successful = true;

		return Result; // Successful result
	}
	else
	{
		ensureMsgf( false, TEXT( "Function map is probably setup wrong with Item Type ID" ) );

		return Result; // Empty unsuccessful result
	}
}
