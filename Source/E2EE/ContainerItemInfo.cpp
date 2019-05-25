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
}

UItemInfo* UContainerItemInfo::GetContainedItem()
{
	return ContainedItem;
}

int UContainerItemInfo::GetLockId()
{
	return CurrentLock->GetLockId();
}

UContainerItemInfo* UContainerItemInfo::Duplicate()
{
	UContainerItemInfo* Clone = NewObject<UContainerItemInfo>();

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

void UContainerItemInfo::LockUp( ULockItemInfo* InLock )
{
	CurrentLock = InLock;

	OnLocked.Broadcast();
}

void UContainerItemInfo::Unlock( UKeyItemInfo* Key )
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
