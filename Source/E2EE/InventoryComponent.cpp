// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryComponent.h"

#include "Classes/GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Blueprint/UserWidget.h"

UInventoryComponent::UInventoryComponent()
{

}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	InventoryWidget = CreateWidget<UUserWidget>( GetWorld()->GetFirstPlayerController(), InventoryWidgetClass );
}

void UInventoryComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}

void UInventoryComponent::AddItem( FItem NewItem )
{
	Items.Add( NewItem );

	UE_LOG( LogTemp, Warning, TEXT( "Item added" ) );

	// Testing. It should be called from a keyboard event.
	DisplayInventory();
}

void UInventoryComponent::DisplayInventory()
{
	if ( InventoryWidget )
	{
		InventoryWidget->AddToViewport();
	}
	else
	{
		UE_LOG( LogTemp, Warning, TEXT( "No inventory widget!" ) );
	}
}
