#include "Lock.h"

#include "PickupComponent.h"
#include "HighlightComponent.h"
#include "LockItemInfo.h"
#include "LockItemWidget.h"

#include "Components/StaticMeshComponent.h"

ALock::ALock()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "StaticMesh" ) );
	StaticMeshComponent->SetupAttachment( RootComponent );

	PickupComponent = CreateDefaultSubobject<UPickupComponent>( TEXT( "Pickup" ) );

	HightlightComponent = CreateDefaultSubobject<UHighlightComponent>( TEXT( "Highlight" ) );

	LockItemInfo = NewObject<ULockItemInfo>();
}

UItemInfo* ALock::GetItemInfo()
{
	return LockItemInfo;
}

int ALock::GetLockId()
{
	return LockItemInfo->GetLockId();
}

void ALock::SetLockId( int InLockId )
{
	LockItemInfo->SetLockId( InLockId );
}
