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

	// Bind UItemMenu events.
	ItemMenu->OnButtonDestroyClicked.AddDynamic( this, &UInventoryMenu::HandleOnItemMenuButtonDestroyClicked );
	ItemMenu->OnButtonDropClicked.AddDynamic( this, &UInventoryMenu::HandleOnItemMenuButtonDropClicked );
	ItemMenu->OnButtonOpenClicked.AddDynamic( this, &UInventoryMenu::HandleOnItemMenuButtonOpenClicked );
	ItemMenu->OnButtonForCombinationClicked.AddDynamic( this, &UInventoryMenu::HandleOnItemMenuButtonForCombinationClicked );

	// Bind my input events.
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

#pragma region My UI event handlers
void UInventoryMenu::HandleOnItemClickerClicked( UItemClicker* ClickedItemClicker )
{
	AItem* TargetItem = ClickedItemClicker->GetItem();

	if ( bIsCombining )
	{
		TArray<AItem*> CombiningItems;
		CombiningItems.Add( FirstItemForCombination );
		CombiningItems.Add( TargetItem );

		Inventory->CombineItems( CombiningItems );

		bIsCombining = false;
	}
	else
	{
		ItemMenu->Display( TargetItem );

		FirstItemForCombination = TargetItem;
	}
}

void UInventoryMenu::HandleOnButtonHideInventoryMenuClicked()
{
	RemoveFromParent();
}
#pragma endregion

#pragma region Item Menu event handlers
void UInventoryMenu::HandleOnItemMenuButtonDestroyClicked( AItem* TargetItem )
{
	Inventory->RemoveItem( TargetItem );
}

void UInventoryMenu::HandleOnItemMenuButtonDropClicked( AItem* TargetItem )
{
	Inventory->DropItem( TargetItem );
}

void UInventoryMenu::HandleOnItemMenuButtonOpenClicked( AItem* TargetItem )
{
	Inventory->OpenItem( TargetItem );
}

void UInventoryMenu::HandleOnItemMenuButtonForCombinationClicked( AItem* TargetItem )
{
	bIsCombining = true;
}
#pragma endregion

#pragma region Inventory event handlers
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
#pragma endregion
