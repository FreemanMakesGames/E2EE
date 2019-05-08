#include "InventoryMenu.h"

#include "ItemClicker.h"
#include "ItemMenu.h"
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

	/* Input events */

	Button_HideInventoryMenu->OnClicked.AddDynamic( this, &UInventoryMenu::HandleOnButtonHideInventoryMenuClicked );
}

/**
 * Show a specified Inventory.
 * Only reload and reset if it's a different inventory.
 */
void UInventoryMenu::ShowInventory( UInventory* InventoryToSet )
{
	if ( !InventoryToSet )
	{
		UE_LOG( LogTemp, Error, TEXT( "UInventoryMenu.ShowInventory: InventoryToSet is nullptr!" ) );
		return;
	}

	if ( Inventory != InventoryToSet )
	{
		if ( Inventory )
		{
			Inventory->OnItemAdded.RemoveAll( this );
			Inventory->OnItemRemoved.RemoveAll( this );
		}

		Inventory = InventoryToSet;

		ReloadInventoryDisplay();

		Inventory->OnItemAdded.AddDynamic( this, &UInventoryMenu::HandleOnItemAdded );
		Inventory->OnItemRemoved.AddDynamic( this, &UInventoryMenu::HandleOnItemRemoved );
	}

	AddToViewport();
}

/**
 * Create a new ItemClicker with ItemWidget content, and add it to the WrapBox.
 */
UItemClicker* UInventoryMenu::AddNewItemClicker( AItem* Item )
{
	UItemClicker* ItemClicker = CreateWidget<UItemClicker>( this, ItemClickerClass );

	ItemClicker->SetItem( Item );

	ItemClicker->OnClicked.AddDynamic( this, &UInventoryMenu::HandleOnItemClickerClicked );

	WrapBox_ItemClickers->AddChildWrapBox( ItemClicker );

	return ItemClicker;
}

/**
 * Remove all the ItemClickers.
 * Add new ItemClickers based on Inventory's Items.
 */
void UInventoryMenu::ReloadInventoryDisplay()
{
	WrapBox_ItemClickers->ClearChildren();

	if ( !Inventory )
	{
		UE_LOG( LogTemp, Warning, TEXT( "UInventoryMenu.ReloadInventoryDisplay: Inventory is nullptr!" ) );	
		return;
	}

	TArray<AItem*> Items = Inventory->GetItems();

	for ( int i = 0; i < Items.Num(); i++ )
	{
		UItemClicker* ItemClicker = AddNewItemClicker( Items[ i ] );
	}
}

void UInventoryMenu::HandleOnItemClickerClicked( UItemClicker* ClickedItemClicker )
{
	ItemMenu->ShowButtons( ClickedItemClicker->GetItem() );
}

void UInventoryMenu::HandleOnButtonHideInventoryMenuClicked()
{
	RemoveFromParent();
}

void UInventoryMenu::HandleOnItemAdded( AItem* ItemAdded )
{
	AddNewItemClicker( ItemAdded );
}

void UInventoryMenu::HandleOnItemRemoved( AItem* ItemRemoved )
{
	UE_LOG( LogTemp, Warning, TEXT( "Item removal" ) );
}
