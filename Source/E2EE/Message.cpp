#include "Message.h"

#include "MessageItemInfo.h"

void AMessage::BeginPlay()
{
	Super::BeginPlay();

	MessageItemInfo = NewObject<UMessageItemInfo>( this );
}

UItemInfo* AMessage::GetItemInfo()
{
	return MessageItemInfo;
}
