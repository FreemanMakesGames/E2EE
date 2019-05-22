#include "KeyItem.h"

#include "PickupComponent.h"
#include "HighlightComponent.h"
#include "KeyItemInfo.h"
#include "KeyItemWidget.h"

#include "Components/StaticMeshComponent.h"

AKeyItem::AKeyItem()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "StaticMesh" ) );
	StaticMeshComponent->SetupAttachment( RootComponent );

	PickupComponent = CreateDefaultSubobject<UPickupComponent>( TEXT( "Pickup" ) );

	HightlightComponent = CreateDefaultSubobject<UHighlightComponent>( TEXT( "Highlight" ) );
}

void AKeyItem::BeginPlay()
{
	Super::BeginPlay();

	KeyItemWidget = CreateWidget<UKeyItemWidget>( GetWorld()->GetFirstPlayerController() );
}

UItemInfo* AKeyItem::GetItemInfo()
{
	return KeyItemInfo;
}

UItemWidget* AKeyItem::GetItemWidget()
{
	return KeyItemWidget;
}
