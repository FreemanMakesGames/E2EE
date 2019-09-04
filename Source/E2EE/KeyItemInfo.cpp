#include "KeyItemInfo.h"

#include "KeyItem.h"
#include "KeyItemWidget.h"

#include "UObject/ConstructorHelpers.h"

UKeyItemInfo::UKeyItemInfo()
{
	static ConstructorHelpers::FClassFinder<AKeyItem> KeyItemClassFinder( TEXT( "/Game/Items/Blueprints/BP_Key" ) );
	ItemClass = KeyItemClassFinder.Class;

	static ConstructorHelpers::FClassFinder<UKeyItemWidget> KeyItemWidgetClassFinder( TEXT( "/Game/UI/InventorySystem/ItemWidgets/WBP_Key" ) );
	ItemWidgetClass = KeyItemWidgetClassFinder.Class;

	ItemUsages.Add( EItemUsage::Unlock );
	ItemUsages.Add( EItemUsage::Duplicate );
	ItemUsages.Add( EItemUsage::Drop );
	ItemUsages.Add( EItemUsage::Destroy );

	ItemTypeId = 1;
}

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
	ensure( GetWorld() );

	UKeyItemInfo* Clone = NewObject<UKeyItemInfo>( GetWorld() );

	Clone->SetKeyId( KeyId );

	return Clone;
}

FText UKeyItemInfo::Describe()
{
	FFormatNamedArguments Args;
	Args.Add( "ID", KeyId );

	return FText::Format( NSLOCTEXT( "", "", "Key '{ID}'" ), Args );
}
