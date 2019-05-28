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
	ItemMenu->OnButtonDuplicateClicked.AddDynamic( this, &UInventoryMenu::HandleOnItemMenuButtonDuplicateClicked );
	ItemMenu->OnButtonOpenClicked.AddDynamic( this, &UInventoryMenu::HandleOnItemMenuButtonOpenClicked );
	ItemMenu->OnButtonReadClicked.AddDynamic( this, &UInventoryMenu::HandleOnItemMenuButtonReadClicked );
	ItemMenu->OnButtonForCombinationClicked.AddDynamic( this, &UInventoryMenu::HandleOnItemMenuButtonForCombinationClicked );

	// Bind my input events.
	Button_HideInventoryMenu->OnClicked.AddDynamic( this, &UInventoryMenu::HandleOnButtonHideInventoryMenuClicked );
}

/**
 * Show a specified Inventory.
 * Only reload and reset if it's a different inventory.
 */
void UInventoryMenu::ShowInventory( UInventory* TargetInventory )
{
	if ( !TargetInventory )
	{
		ensureAlways( false );
		return;
	}

	if ( Inventory != TargetInventory )
	{
		if ( Inventory )
		{
			Inventory->OnItemAdded.RemoveAll( this );
			Inventory->OnItemRemoved.RemoveAll( this );
		}

		Inventory = TargetInventory;

		ReloadInventoryDisplay();

		Inventory->OnItemAdded.AddDynamic( this, &UInventoryMenu::HandleOnItemAdded );
		Inventory->OnItemRemoved.AddDynamic( this, &UInventoryMenu::HandleOnItemRemoved );
	}

	AddToViewport();
}

void UInventoryMenu::HideInventory()
{
	bIsCombining = false;

	if ( ItemMenu->IsInViewport() )
	{
		ItemMenu->RemoveFromParent();
	}

	RemoveFromParent();
}

/**
 * Create a new ItemClicker with ItemWidget content, and add it to the WrapBox.
 */
UItemClicker* UInventoryMenu::AddNewItemClicker( UItemInfo* Item )
{
	UItemClicker* ItemClicker = CreateWidget<UItemClicker>( this, ItemClickerClass );

	ItemClicker->SetItemInfo( Item );

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
		ensureAlways( false );
		return;
	}

	TArray<UItemInfo*> Items = Inventory->GetItems();

	for ( int i = 0; i < Items.Num(); i++ )
	{
		if ( ensureAlways( Items[i] ) )
		{
			UItemClicker* ItemClicker = AddNewItemClicker( Items[i] );
		}
	}
}

#pragma region My UI event handlers
void UInventoryMenu::HandleOnItemClickerClicked( UItemClicker* ClickedItemClicker )
{
	UItemInfo* TargetItem = ClickedItemClicker->GetItemInfo();

	if ( bIsCombining )
	{
		TArray<UItemInfo*> CombiningItems;
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
	HideInventory();
}
#pragma endregion

#pragma region Item Menu event handlers
void UInventoryMenu::HandleOnItemMenuButtonDestroyClicked( UItemInfo* TargetItem )
{
	Inventory->RemoveItem( TargetItem );
}

void UInventoryMenu::HandleOnItemMenuButtonDropClicked( UItemInfo* TargetItem )
{
	Inventory->DropItem( TargetItem );
}

void UInventoryMenu::HandleOnItemMenuButtonDuplicateClicked( UItemInfo* TargetItem )
{
	Inventory->ServerDuplicateItem( TargetItem );
}

void UInventoryMenu::HandleOnItemMenuButtonOpenClicked( UItemInfo* TargetItem )
{
	Inventory->OpenItem( TargetItem );
}

void UInventoryMenu::HandleOnItemMenuButtonReadClicked( UItemInfo* TargetItem )
{
	Inventory->ReadItem( TargetItem );
}

void UInventoryMenu::HandleOnItemMenuButtonForCombinationClicked( UItemInfo* TargetItem )
{
	bIsCombining = true;
}
#pragma endregion

#pragma region Inventory event handlers
void UInventoryMenu::HandleOnItemAdded( UItemInfo* ItemAdded )
{
	UItemClicker* ItemClicker = AddNewItemClicker( ItemAdded );
}

void UInventoryMenu::HandleOnItemRemoved( UItemInfo* ItemRemoved )
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
