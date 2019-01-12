// Fill out your copyright notice in the Description page of Project Settings.

#include "PickupComponent.h"
#include "Item.h"
#include "InventoryComponent.h"

#include "Components/PrimitiveComponent.h"
#include "Engine/Classes/GameFramework/PlayerController.h"

// Sets default values for this component's properties
UPickupComponent::UPickupComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//PrimaryComponentTick.bCanEverTick = true;

	if ( GetOwner() )
	{
		UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>( GetOwner()->GetComponentByClass( UPrimitiveComponent::StaticClass() ) );
		if ( PrimitiveComponent )
		{
			PrimitiveComponent->OnClicked.AddDynamic( this, &UPickupComponent::Pickup );
		}
	}

}


// Called when the game starts
void UPickupComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

void UPickupComponent::Pickup( UPrimitiveComponent* TouchedComponent, FKey ButtonPressed )
{
	UE_LOG( LogTemp, Warning, TEXT( "Item clicked" ) );

	if ( ItemReceiver )
	{
		UInventoryComponent* InventoryComponent = Cast<UInventoryComponent>( ItemReceiver->GetComponentByClass( UInventoryComponent::StaticClass() ) );
		if ( InventoryComponent )
		{
			FItem NewItem { "Temp item" };

			InventoryComponent->AddItem( NewItem );
		}
	}
}

// Called every frame
void UPickupComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}
