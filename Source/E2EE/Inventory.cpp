// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory.h"

#include "Item.h"

void UInventory::AddItem( AItem* ItemToAdd )
{
	Items.Add( ItemToAdd );
}

void UInventory::RemoveItem( AItem* ItemToRemove )
{
	Items.Remove( ItemToRemove );
}

int UInventory::CountItems()
{
	return Items.Num();
}
