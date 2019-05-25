#include "Lock.h"

#include "PickupComponent.h"
#include "HighlightComponent.h"
#include "LockItemInfo.h"
#include "LockItemWidget.h"

#include "Components/StaticMeshComponent.h"

ALock::ALock( const FObjectInitializer& ObjectInitializer ) : Super( ObjectInitializer )
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "StaticMesh" ) );
	StaticMeshComponent->SetupAttachment( RootComponent );

	PickupComponent = CreateDefaultSubobject<UPickupComponent>( TEXT( "Pickup" ) );

	HightlightComponent = CreateDefaultSubobject<UHighlightComponent>( TEXT( "Highlight" ) );
}
