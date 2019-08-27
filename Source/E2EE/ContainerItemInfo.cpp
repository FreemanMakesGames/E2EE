#include "ContainerItemInfo.h"

#include "Container.h"
#include "ContainerItemWidget.h"
#include "LockItemInfo.h"
#include "DevUtilities.h"

#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"

UContainerItemInfo::UContainerItemInfo()
{
	static ConstructorHelpers::FClassFinder<AContainer> ContainerItemClassFinder( TEXT( "/Game/Items/Blueprints/BP_Container" ) );
	ItemClass = ContainerItemClassFinder.Class;

	static ConstructorHelpers::FClassFinder<UContainerItemWidget> ContainerItemWidgetClassFinder( TEXT( "/Game/UI/InventorySystem/ItemWidgets/WBP_Container" ) );
	ItemWidgetClass = ContainerItemWidgetClassFinder.Class;

	ItemUsages.Add( EItemUsage::Open );
	ItemUsages.Add( EItemUsage::Contain );
	ItemUsages.Add( EItemUsage::Duplicate );
	ItemUsages.Add( EItemUsage::Drop );
	ItemUsages.Add( EItemUsage::Destroy );

	ItemTypeId = 2;
}

UItemInfo* UContainerItemInfo::GetContainedItem()
{
	return ContainedItem;
}

int UContainerItemInfo::GetLockId()
{
	return CurrentLock->GetLockId();
}

ULockItemInfo* UContainerItemInfo::GetLock()
{
	return CurrentLock;
}

UContainerItemInfo* UContainerItemInfo::Duplicate()
{
	ensure( GetWorld() );

	UContainerItemInfo* Clone = NewObject<UContainerItemInfo>( GetWorld() );

	if ( IsOccupied() )
	{
		ensureMsgf( !Cast<UContainerItemInfo>( ContainedItem ), TEXT( "This container contains another container!!!" ) );

		Clone->ContainItem( ContainedItem->Duplicate() );
	}

	if ( IsLocked() )
	{
		Clone->LockUp( CurrentLock->Duplicate() );
	}

	return Clone;
}

void UContainerItemInfo::ContainItem( UItemInfo* TargetItem )
{
	ContainedItem = TargetItem;

	OnOccupied.Broadcast();
}

UItemInfo* UContainerItemInfo::ReleaseItem()
{
	if ( IsOccupied() )
	{
		UItemInfo* ItemToRelease = ContainedItem;

		ContainedItem = nullptr;

		OnVacated.Broadcast();

		return ItemToRelease;
	}
	else
	{
		UDevUtilities::PrintError( TEXT( "Container's ReleaseItem is called before checking if it's occupied!" ) );

		return nullptr;
	}
}

/** Simply set the lock. IsLocked should be checked outside. */
void UContainerItemInfo::LockUp( ULockItemInfo* InLock )
{
	CurrentLock = InLock;

	OnLocked.Broadcast();
}

/** Simply unset the lock. ID checks should be done outside. */
void UContainerItemInfo::Unlock()
{
	CurrentLock = nullptr;

	OnUnlocked.Broadcast();
}

bool UContainerItemInfo::IsOccupied()
{
	return ( IsValid( ContainedItem ) );
}

bool UContainerItemInfo::IsLocked()
{
	return ( IsValid( CurrentLock ) );
}
