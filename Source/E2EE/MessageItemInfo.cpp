#include "MessageItemInfo.h"

UMessageItemInfo* UMessageItemInfo::Duplicate()
{
	UMessageItemInfo* Clone = NewObject<UMessageItemInfo>();

	return Clone;
}
