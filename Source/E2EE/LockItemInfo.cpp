#include "LockItemInfo.h"

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
