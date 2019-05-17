#include "DropItemComponent.h"

#include "GameUtilities.h"
#include "Item.h"

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

void UDropItemComponent::ServerDropItem_Implementation( AItem* ItemToDrop )
{
	UPrimitiveComponent* PrimitiveComponent = ItemToDrop->FindComponentByClass<UPrimitiveComponent>();

	if ( PrimitiveComponent )
	{
		UGameUtilities::EnableActor( ItemToDrop );

		ItemToDrop->SetActorTransform( GetComponentTransform() );
	}
	else
	{
		UE_LOG( LogTemp, Error, TEXT( "UDropItemComponent tries to drop %s, which doesn't have a UPrimitiveComponent!" ) );
	}
}

bool UDropItemComponent::ServerDropItem_Validate( AItem* ItemToDrop )
{
	return true;
}

