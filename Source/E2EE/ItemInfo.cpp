#include "ItemInfo.h"

int UItemInfo::GetItemId()
{
	return ItemTypeId;
}

void UItemInfo::SetItemId( int InItemId )
{
	ItemTypeId = InItemId;
}
