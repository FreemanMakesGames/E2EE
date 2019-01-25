// Fill out your copyright notice in the Description page of Project Settings.

#include "PickupComponent.h"
#include "InventoryComponent.h"
#include "MyPlayerController.h"
#include "E2EECharacter.h"

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

void UPickupComponent::Pickup( UPrimitiveComponent* TouchedComponent, FKey ButtonPressed )
{
	UE_LOG( LogTemp, Display, TEXT( "%s is attempted to be picked up." ), *MyOwner->GetName() );

	AMyPlayerController* PlayerController = Cast<AMyPlayerController>( GetWorld()->GetFirstPlayerController() );

	AE2EECharacter* ItemReceiver = PlayerController->GetActiveCharacter();

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
