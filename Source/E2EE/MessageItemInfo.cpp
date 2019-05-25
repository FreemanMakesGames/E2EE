#include "MessageItemInfo.h"

#include "Message.h"
#include "MessageItemWidget.h"

#include "UObject/ConstructorHelpers.h"

UMessageItemInfo::UMessageItemInfo()
{
	static ConstructorHelpers::FClassFinder<AMessage> MessageItemClassFinder( TEXT( "/Game/Items/Blueprints/BP_Message" ) );
	ItemClass = MessageItemClassFinder.Class;

	static ConstructorHelpers::FClassFinder<UMessageItemWidget> MessageItemWidgetClassFinder( TEXT( "/Game/UI/InventorySystem/ItemWidgets/WBP_Message" ) );
	ItemWidgetClass = MessageItemWidgetClassFinder.Class;
}

UMessageItemInfo* UMessageItemInfo::Duplicate()
{
	UMessageItemInfo* Clone = NewObject<UMessageItemInfo>();

	return Clone;
}
