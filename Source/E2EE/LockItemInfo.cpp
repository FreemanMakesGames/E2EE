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
	ULockItemInfo* Clone = NewObject<ULockItemInfo>();

	Clone->SetLockId( LockId );

	return Clone;
}
