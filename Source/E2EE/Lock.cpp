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
}

void ALock::BeginPlay()
{
	Super::BeginPlay();

	LockItemWidget = CreateWidget<ULockItemWidget>( GetWorld()->GetFirstPlayerController() );
}

void ALock::SetLockId( int InLockId )
{
	LockItemInfo->SetLockId( InLockId );

	LockItemWidget->SetLockIdText( InLockId );
}

UItemInfo* ALock::GetItemInfo()
{
	return LockItemInfo;
}

UUserWidget* ALock::GetItemWidget()
{
	return LockItemWidget;
}
