#include "ContainerItemInfo.h"

#include "ContainerItemWidget.h"
#include "LockItemInfo.h"

#include "Engine/Engine.h"

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
		GEngine->AddOnScreenDebugMessage( -1, 100.0f, FColor::Red, TEXT( "Container's ReleaseItem is called before checking if it's occupied!" ) );

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
