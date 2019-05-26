#include "ItemCombiner.h"

#include "Item.h"
#include "ItemInfo.h"
#include "LockItemInfo.h"
#include "KeyItemInfo.h"
#include "ContainerItemInfo.h"
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
	UDevUtilities::PrintInfo( "Lock container!" );

	return SourceItems;
}

TArray<UItemInfo*> UItemCombiner::UnlockContainer( TArray<UItemInfo*> SourceItems )
{
	UDevUtilities::PrintInfo( "Unlock container!" );

	return SourceItems;
}
