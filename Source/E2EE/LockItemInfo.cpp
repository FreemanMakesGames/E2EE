#include "LockItemInfo.h"

#include "Lock.h"
#include "LockItemWidget.h"

#include "UObject/ConstructorHelpers.h"

ULockItemInfo::ULockItemInfo()
{
	static ConstructorHelpers::FClassFinder<ALock> LockItemClassFinder( TEXT( "/Game/Items/Blueprints/BP_Lock" ) );
	ItemClass = LockItemClassFinder.Class;

	static ConstructorHelpers::FClassFinder<ULockItemWidget> LockItemWidgetClassFinder( TEXT( "/Game/UI/InventorySystem/ItemWidgets/WBP_Lock" ) );
	ItemWidgetClass = LockItemWidgetClassFinder.Class;

	ItemUsages.Add( EItemUsage::Lock );
	ItemUsages.Add( EItemUsage::Duplicate );
	ItemUsages.Add( EItemUsage::Drop );
	ItemUsages.Add( EItemUsage::Destroy );

	ItemTypeId = 0;
}

int ULockItemInfo::GetLockId()
{
	return LockId;
}

void ULockItemInfo::SetLockId( int InLockId )
{
	LockId = InLockId;
}

ULockItemInfo* ULockItemInfo::Duplicate()
{
	ensure( GetWorld() );

	ULockItemInfo* Clone = NewObject<ULockItemInfo>( GetOuter() );

	Clone->SetLockId( LockId );

	return Clone;
}
