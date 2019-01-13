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

void UInventoryComponent::AddItem( FItem NewItem )
{
	Items.Add( NewItem );

	UE_LOG( LogTemp, Display, TEXT( "%s is picked up." ), *NewItem.Name );
}
