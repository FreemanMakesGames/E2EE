#include "ItemCombiner.h"

#include "Item.h"
#include "ItemInfo.h"
#include "DevUtilities.h"

#include "UObject/ConstructorHelpers.h"
#include "Templates/Function.h"

UItemCombiner::UItemCombiner()
{
	/* All classes of combinable Items */

	static ConstructorHelpers::FClassFinder<AItem> LockClassFinder( TEXT( "/Game/Items/Blueprints/BP_Lock" ) );
	TSubclassOf<AItem> LockClass = LockClassFinder.Class;

	static ConstructorHelpers::FClassFinder<AItem> KeyClassFinder( TEXT( "/Game/Items/Blueprints/BP_Key" ) );
	TSubclassOf<AItem> KeyClass = KeyClassFinder.Class;

	static ConstructorHelpers::FClassFinder<AItem> ContainerClassFinder( TEXT( "/Game/Items/Blueprints/BP_Container" ) );
	TSubclassOf<AItem> ContainerClass = ContainerClassFinder.Class;

	static ConstructorHelpers::FClassFinder<AItem> MessageClassFinder( TEXT( "/Game/Items/Blueprints/BP_Message" ) );
	TSubclassOf<AItem> MessageClass = MessageClassFinder.Class;

	/* All possible combination among Item types */

	TArray<TSubclassOf<AItem>> LockAndContainer;
	LockAndContainer.Add( LockClass );
	LockAndContainer.Add( ContainerClass );
	FArrayOfItemClasses ArrayOfLockAndContainerClasses( LockAndContainer );
	FunctionMap.Add( ArrayOfLockAndContainerClasses, &UItemCombiner::LockContainer );

	TArray<TSubclassOf<AItem>> KeyAndContainer;
	KeyAndContainer.Add( KeyClass );
	KeyAndContainer.Add( ContainerClass );
	FArrayOfItemClasses ArrayOfKeyAndContainerClasses( KeyAndContainer );
	FunctionMap.Add( ArrayOfKeyAndContainerClasses, &UItemCombiner::UnlockContainer );

	TArray<TSubclassOf<AItem>> ContainerAndLock;
	ContainerAndLock.Add( ContainerClass );
	ContainerAndLock.Add( LockClass );

	TArray<TSubclassOf<AItem>> ContainerAndKey;
	ContainerAndKey.Add( ContainerClass );
	ContainerAndKey.Add( KeyClass );

	TArray<TSubclassOf<AItem>> ContainerAndMessage;
	ContainerAndMessage.Add( ContainerClass );
	ContainerAndMessage.Add( MessageClass );
}

TArray<UItemInfo*> UItemCombiner::CombineItems(TArray<UItemInfo*> SourceItems)
{
	FArrayOfItemClasses SourceItemClasses;
	for ( int i = 0; i < SourceItems.Num(); i++ )
	{
		SourceItemClasses.ItemClasses.Add( SourceItems[i]->GetClass() );
	}

	FCombineFunction* CombineFunctionPointer = FunctionMap.Find( SourceItemClasses );
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
	UDevUtilities::PrintInfo( "Lock container!" );

	return SourceItems;
}

TArray<UItemInfo*> UItemCombiner::UnlockContainer( TArray<UItemInfo*> SourceItems )
{
	UDevUtilities::PrintInfo( "Unlock container!" );

	return SourceItems;
}
