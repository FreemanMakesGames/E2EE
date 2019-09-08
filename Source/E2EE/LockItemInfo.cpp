#include "LockItemInfo.h"

#include "Lock.h"
#include "LockItemWidget.h"

#include "UObject/ConstructorHelpers.h"

ULockItemInfo::ULockItemInfo()
{
	static ConstructorHelpers::FClassFinder<ALock> LockItemClassFinder( TEXT( "/Game/Items/Blueprints/BP_Lock" ) );
	ItemClass = LockItemClassFinder.Class;

	static ConstructorHelpers::FClassFinder<ULockItemWidget> LockItemWidgetClassFinder( TEXT( "/Game/UI/InventorySystem/ItemWidgets/WBP_Lock" ) );
	ItemWidgetClass = LockItemWidgetClassFinder.Class;

	ItemUsages.Add( EItemUsage::Lock );
	ItemUsages.Add( EItemUsage::Duplicate );
	ItemUsages.Add( EItemUsage::Drop );
	ItemUsages.Add( EItemUsage::Destroy );

	ItemTypeId = 0;
}

FString ULockItemInfo::GetLockId()
{
	return LockId;
}

void ULockItemInfo::SetLockId( FString InLockId )
{
	LockId = InLockId;
}

ULockItemInfo* ULockItemInfo::Duplicate()
{
	ensure( GetWorld() );

	ULockItemInfo* Clone = NewObject<ULockItemInfo>( GetOuter() );

	Clone->SetLockId( LockId );

	return Clone;
}

FText ULockItemInfo::Describe()
{
	FFormatNamedArguments Args;
	Args.Add( "ID", FText::FromString( LockId ) );

	return FText::Format( NSLOCTEXT( "", "", "Lock '{ID}'" ), Args );
}

bool ULockItemInfo::IsEquivalentTo( UItemInfo* OtherItem )
{
	if ( ULockItemInfo* OtherLock = Cast<ULockItemInfo>( OtherItem ) )
	{
		return LockId == OtherLock->GetLockId();
	}

	return false;
}
