// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryComponent.h"

//#include "Classes/GameFramework/PlayerController.h"
//#include "Engine/World.h"
//#include "Blueprint/UserWidget.h"

UInventoryComponent::UInventoryComponent()
{

}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

TArray<FItem> UInventoryComponent::GetItems() { return Items; }

void UInventoryComponent::AddItem( FItem NewItem )
{
	Items.Add( NewItem );
}
