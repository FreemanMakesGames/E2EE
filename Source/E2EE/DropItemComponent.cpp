#include "DropItemComponent.h"

#include "Item.h"
#include "ItemInfo.h"
#include "BasicGameState.h"
#include "DevUtilities.h"

#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"

UDropItemComponent::UDropItemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UDropItemComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UDropItemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UDropItemComponent::ServerDropItem_Implementation( UItemInfo* ItemToDrop )
{
	MulticastDropItem( ItemToDrop );
}

bool UDropItemComponent::ServerDropItem_Validate( UItemInfo* ItemToDrop )
{
	return true;
}

void UDropItemComponent::MulticastDropItem_Implementation( UItemInfo* ItemToDrop )
{
	if ( !ItemToDrop )
	{
		UE_LOG( LogTemp, Error, TEXT( "Server is dropping a null AItem!" ) );
		return;
	}

	GetWorld()->SpawnActor<AItem>( ItemToDrop->GetItemClass(), GetComponentTransform() );
}
