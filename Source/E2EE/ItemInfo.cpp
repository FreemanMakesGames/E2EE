#include "ItemInfo.h"

int UItemInfo::GetItemTypeId()
{
	return ItemTypeId;
}

void UItemInfo::SetItemTypeId( int InItemTypeId )
{
	ItemTypeId = InItemTypeId;
}

TArray<EItemUsage> UItemInfo::GetItemUsages()
{
	return ItemUsages;
}
