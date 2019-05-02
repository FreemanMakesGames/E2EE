// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryMenu.h"

#include "ItemClicker.h"
#include "Inventory.h"
#include "Item.h"
#include "ItemWidget.h"

#include "Components/WrapBox.h"
#include "Components/Button.h"
#include "Components/NamedSlot.h"

void UInventoryMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UE_LOG( LogTemp, Warning, TEXT( "UInventoryMenu.NativeOnInitialized" ) );

	/* Error checking */

	if ( !ItemClickerClass )
	{
		UE_LOG( LogTemp, Error, TEXT( "InventoryMenu's ItemClickerClass isn't assigned!" ) );
		return;
	}

	Button_HideInventoryMenu->OnClicked.AddDynamic( this, &UInventoryMenu::HandleOnButtonHideInventoryMenuClicked );
}

UInventory* UInventoryMenu::GetInventory()
{
	return Inventory;
}

void UInventoryMenu::SetInventory( UInventory* InventoryToSet )
{
	Inventory = InventoryToSet;

	ReloadDisplay();
}

void UInventoryMenu::ReloadDisplay()
{
	if ( !Inventory )
	{
		UE_LOG( LogTemp, Warning, TEXT( "InventoryMenu doesn't have an inventory!" ) );

		WrapBox_ItemClickers->ClearChildren();

		return;
	}

	for ( int i = 0; i < Inventory->CountItems(); i++ )
	{
		UItemClicker* NewItemClicker = CreateWidget<UItemClicker>( this, ItemClickerClass );

		// TODO: Inventory: Setup NewItemClicker based on each item.
		NewItemClicker->GetItemWidgetSlot()->AddChild( Inventory->GetItems()[i]->GetItemWidget() );

		NewItemClicker->OnClicked.AddDynamic( this, &UInventoryMenu::HandleOnItemClickerClicked );

		WrapBox_ItemClickers->AddChildWrapBox( NewItemClicker );
	}
}

void UInventoryMenu::HandleOnItemClickerClicked( UItemClicker* ClickedItemClicker )
{
	UE_LOG( LogTemp, Warning, TEXT( "Event test: %s" ), *ClickedItemClicker->GetName() );

	// TODO: Inventory: Update and show ItemMenu here.
}

void UInventoryMenu::HandleOnButtonHideInventoryMenuClicked()
{
	RemoveFromParent();
}
