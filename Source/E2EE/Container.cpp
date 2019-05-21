#include "Container.h"

#include "PickupComponent.h"
#include "HighlightComponent.h"
#include "ContainerItemInfo.h"
#include "ContainerItemWidget.h"

#include "Components/StaticMeshComponent.h"

AContainer::AContainer()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "StaticMesh" ) );
	StaticMeshComponent->SetupAttachment( RootComponent );

	PickupComponent = CreateDefaultSubobject<UPickupComponent>( TEXT( "Pickup" ) );

	HightlightComponent = CreateDefaultSubobject<UHighlightComponent>( TEXT( "Highlight" ) );
}

void AContainer::BeginPlay()
{
	Super::BeginPlay();

	ContainerItemWidget = CreateWidget<UContainerItemWidget>( GetWorld()->GetFirstPlayerController() );
}

UItemInfo* AContainer::GetItemInfo()
{
	return ContainerItemInfo;
}

UUserWidget* AContainer::GetItemWidget()
{
	return ContainerItemWidget;
}
