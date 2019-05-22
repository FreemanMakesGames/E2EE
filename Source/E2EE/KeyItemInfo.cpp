#include "KeyItemInfo.h"

int UKeyItemInfo::GetKeyId()
{
	return KeyId;
}

void UKeyItemInfo::SetKeyId( int InKeyId )
{
	KeyId = InKeyId;
}

UKeyItemInfo* UKeyItemInfo::Duplicate()
{
	UKeyItemInfo* Clone = NewObject<UKeyItemInfo>();

	Clone->SetKeyId( KeyId );

	return Clone;
}
