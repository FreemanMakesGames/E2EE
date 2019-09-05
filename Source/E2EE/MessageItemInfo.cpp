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

	ItemUsages.Add( EItemUsage::Read );
	ItemUsages.Add( EItemUsage::Duplicate );

	ItemTypeId = 3;
}

UMessageItemInfo* UMessageItemInfo::Duplicate()
{
	ensure( GetWorld() );

	UMessageItemInfo* Clone = NewObject<UMessageItemInfo>( GetWorld() );

	return Clone;
}

FText UMessageItemInfo::Describe()
{
	return NSLOCTEXT( "", "", "The Message" );
}

bool UMessageItemInfo::IsEquivalentTo( UItemInfo* OtherItem )
{
	if ( Cast<UMessageItemInfo>( OtherItem ) ) { return true; }

	return false;
}
