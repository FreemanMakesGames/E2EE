#include "Item.h"

#include "ItemWidget.h"

AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
	ItemWidget = CreateWidget<UItemWidget>( GetWorld()->GetFirstPlayerController(), ItemWidgetClass );
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UItemWidget* AItem::GetItemWidget()
{
	return ItemWidget;
}

void AItem::SetItemWidget( UItemWidget* ItemWidgetToSet )
{
	ItemWidget = ItemWidgetToSet;
}

