#include "InventoryMenu.h"

#include "ItemClicker.h"
#include "ItemMenu.h"
#include "Inventory.h"
#include "Item.h"
#include "ItemWidget.h"
#include "DevUtilities.h"

#include "Components/WrapBox.h"
#include "Components/Button.h"
#include "Components/NamedSlot.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UInventoryMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if ( !ItemClickerClass )
	{
		UDevUtilities::PrintError( "InventoryMenu's ItemClickerClass isn't assigned!" );
		return;
	}
}

/**
 * Show a specified Inventory.
 * Only reload and reset if it's a different inventory.
 */
void UInventoryMenu::SetupInventory( UInventory* InInventory )
{
	if ( !InInventory ) { ensureAlways( false ); return; }
	if ( Inventory ) { ensureAlwaysMsgf( false, TEXT( "The current design is one menu for one unique inventory, and no other." ) ); return; }

	Inventory = InInventory;

	Inventory->OnItemAdded.AddDynamic( this, &UInventoryMenu::HandleOnItemAdded );
	Inventory->OnItemRemoved.AddDynamic( this, &UInventoryMenu::HandleOnItemRemoved );

	ensureAlwaysMsgf( !WrapBox_ItemClickers->HasAnyChildren(), TEXT( "Somehow the wrap box already has children?" ) );

	TArray<UItemInfo*> Items = Inventory->GetItems();

	for ( int i = 0; i < Items.Num(); i++ )
	{
		if ( ensureAlways( Items[i] ) )
		{
			UItemClicker* ItemClicker = AddNewItemClicker( Items[i] );
		}
	}
}

void UInventoryMenu::SetupTitle( FText InTitle )
{
	TextBlock_Title->SetText( InTitle );
}

void UInventoryMenu::ShowInventory()
{
	AddToViewport();

	for ( UItemClicker* ItemClicker : ClickersPendingForHighlightForAddition )
	{
		ItemClicker->HighlightForItemAddition();
	}
	ClickersPendingForHighlightForAddition.Empty();
}

/**
 * Create a new ItemClicker with ItemWidget content, and add it to the WrapBox.
 */
UItemClicker* UInventoryMenu::AddNewItemClicker( UItemInfo* Item )
{
	UItemClicker* ItemClicker = CreateWidget<UItemClicker>( this, ItemClickerClass );

	ItemClicker->SetItemInfo( Item );

	ItemClicker->OnClicked.AddDynamic( this, &UInventoryMenu::HandleOnItemClickerClicked );
	ItemClicker->OnAdditionHighlightFinished.AddDynamic( this, &UInventoryMenu::HandleOnClickerAdditionHighlightFinished );

	WrapBox_ItemClickers->AddChildWrapBox( ItemClicker );

	ItemToItemClicker.Add( Item, ItemClicker );

	return ItemClicker;
}

void UInventoryMenu::HandleOnItemClickerClicked( UItemClicker* ClickedItemClicker )
{
	TextBlock_Description->SetText( ClickedItemClicker->GetItemInfo()->Describe() );
}

void UInventoryMenu::HandleOnClickerAdditionHighlightFinished( UItemClicker* HighlightedClicker )
{
	HighlightedClicker->OnAdditionHighlightFinished.RemoveDynamic( this, &UInventoryMenu::HandleOnClickerAdditionHighlightFinished );

	ToggleInput( true );
	
	OnAdditionHighlightCompleted.Broadcast();
}

void UInventoryMenu::HandleOnButtonHideInventoryMenuClicked()
{
	HideInventory();
}

void UInventoryMenu::HandleOnItemAdded( UItemInfo* ItemAdded )
{
	// Highlight animation will play, either now, or after inventory menu is shown.
	// So disable input now. Input will be re-enabled after highlight is finished.
	ToggleInput( false );

	UItemClicker* NewItemClicker = AddNewItemClicker( ItemAdded );

	if ( IsInViewport() )
	{
		NewItemClicker->HighlightForItemAddition();
	}
	else
	{
		ClickersPendingForHighlightForAddition.Add( NewItemClicker );
	}
}

void UInventoryMenu::HandleOnItemRemoved( UItemInfo* ItemRemoved )
{
	UItemClicker** pItemClicker = ItemToItemClicker.Find( ItemRemoved );

	if ( pItemClicker )
	{
		(*pItemClicker)->RemoveFromParent();

		ItemToItemClicker.Remove( ItemRemoved );
	}
	else
	{
		ensureAlwaysMsgf( false, TEXT( "UInventoryMenu hears an Item removal event, but no UItemClicker matches the removed item!" ) );
	}
}

void UInventoryMenu::ToggleInput( bool Enabled )
{
	if ( Enabled )
	{
		//SetVisibility( ESlateVisibility::Visible );

		Image_BlockInput->SetVisibility( ESlateVisibility::Hidden );
	}
	else
	{
		//SetVisibility( ESlateVisibility::HitTestInvisible );

		Image_BlockInput->SetVisibility( ESlateVisibility::Visible );
	}
}

void UInventoryMenu::ClearDescription()
{
	TextBlock_Description->SetText( NSLOCTEXT( "", "", "" ) );
}
