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

FString UKeyItemInfo::GetKeyId()
{
	return KeyId;
}

void UKeyItemInfo::SetKeyId( FString InKeyId )
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
	Args.Add( "ID", FText::FromString( KeyId ) );

	return FText::Format( NSLOCTEXT( "", "", "Key '{ID}'" ), Args );
}

bool UKeyItemInfo::IsEquivalentTo( UItemInfo* OtherItem )
{
	if ( UKeyItemInfo* OtherKey = Cast<UKeyItemInfo>( OtherItem ) )
	{
		return KeyId == OtherKey->GetKeyId();
	}

	return false;
}
