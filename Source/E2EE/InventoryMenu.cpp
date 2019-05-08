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

	ItemMenu->Button_Destroy->OnClicked.AddDynamic( this, &UInventoryMenu::HandleOnItemMenuButtonDestroyClicked );
	ItemMenu->Button_Drop->OnClicked.AddDynamic( this, &UInventoryMenu::HandleOnItemMenuButtonDropClicked );

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

	ItemToItemClicker.Add( Item, ItemClicker );

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
	ClickedItem = ClickedItemClicker->GetItem();

	ItemMenu->ShowButtons( ClickedItemClicker->GetItem() );
}

// FIXME: The ItemMenu should be cleared after destroying an item!
void UInventoryMenu::HandleOnItemMenuButtonDestroyClicked()
{
	Inventory->RemoveItem( ClickedItem );
}

void UInventoryMenu::HandleOnItemMenuButtonDropClicked()
{
	UE_LOG( LogTemp, Warning, TEXT( "Drop" ) );

	// TODO: Inventory: Implement item dropping.
}

void UInventoryMenu::HandleOnButtonHideInventoryMenuClicked()
{
	RemoveFromParent();
}

void UInventoryMenu::HandleOnItemAdded( AItem* ItemAdded )
{
	UItemClicker* ItemClicker = AddNewItemClicker( ItemAdded );
}

void UInventoryMenu::HandleOnItemRemoved( AItem* ItemRemoved )
{
	UItemClicker** pItemClicker = ItemToItemClicker.Find( ItemRemoved );

	if ( pItemClicker )
	{
		(*pItemClicker)->RemoveFromParent();
	}
	else
	{
		UE_LOG( LogTemp, Error, TEXT( "UInventoryMenu hears an Item removal event, but no UItemClicker matches the removed item!" ) );
	}
}
