// Fill out your copyright notice in the Description page of Project Settings.

#include "PickupComponent.h"
#include "InventoryComponent.h"

#include "Components/PrimitiveComponent.h"
#include "Engine/Classes/GameFramework/PlayerController.h"

UPickupComponent::UPickupComponent()
{
	MyOwner = GetOwner();

	if ( MyOwner )
	{
		UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>( GetOwner()->GetComponentByClass( UPrimitiveComponent::StaticClass() ) );
		if ( PrimitiveComponent )
		{
			PrimitiveComponent->OnClicked.AddDynamic( this, &UPickupComponent::Pickup );
		}
	}

}

void UPickupComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPickupComponent::Pickup( UPrimitiveComponent* TouchedComponent, FKey ButtonPressed )
{
	UE_LOG( LogTemp, Warning, TEXT( "Item clicked" ) );

	if ( ItemReceiver )
	{
		UInventoryComponent* InventoryComponent = Cast<UInventoryComponent>( ItemReceiver->GetComponentByClass( UInventoryComponent::StaticClass() ) );
		if ( InventoryComponent )
		{
			InventoryComponent->AddItem( MyItem );

			MyOwner->Destroy();
		}
	}
}

void UPickupComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}
