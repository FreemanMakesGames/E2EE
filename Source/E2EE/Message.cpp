#include "Message.h"

#include "MessageItemInfo.h"

AMessage::AMessage( const FObjectInitializer& ObjectInitializer ) : Super( ObjectInitializer )
{
	//MessageItemInfo = ObjectInitializer.CreateDefaultSubobject<UMessageItemInfo>( this, TEXT( "MessageItemInfo" ) );
}

void AMessage::PostInitProperties()
{
	Super::PostInitProperties();

	MessageItemInfo = NewObject<UMessageItemInfo>( this );
}

UItemInfo* AMessage::GetItemInfo()
{
	return MessageItemInfo;
}
