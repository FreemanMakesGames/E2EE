// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryComponent.h"

UInventoryComponent::UInventoryComponent()
{

}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInventoryComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}

void UInventoryComponent::AddItem( FItem NewItem )
{
	Items.Add( NewItem );

	UE_LOG( LogTemp, Warning, TEXT( "Item added" ) );



}
