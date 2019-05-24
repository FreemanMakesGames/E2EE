#include "Message.h"

#include "MessageItemInfo.h"

AMessage::AMessage()
{
	MessageItemInfo = NewObject<UMessageItemInfo>();
}

UItemInfo* AMessage::GetItemInfo()
{
	return MessageItemInfo;
}
