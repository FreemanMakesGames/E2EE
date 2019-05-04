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

	/* Input events */

	Button_HideInventoryMenu->OnClicked.AddDynamic( this, &UInventoryMenu::HandleOnButtonHideInventoryMenuClicked );

	/* Setup ItemClickers. */

	for ( int i = 0; i < MaxItemSlots; i++ )
	{
		AddNewItemClicker();
	}
}

void UInventoryMenu::ShowInventory( UInventory* InventoryToSet )
{
	if ( Inventory != InventoryToSet )
	{
		Inventory = InventoryToSet;

		ReloadInventoryDisplay();

		Inventory->OnItemAdded.AddDynamic( this, &UInventoryMenu::HandleOnItemAdded );
	}

	AddToViewport();
}

UItemClicker* UInventoryMenu::AddNewItemClicker()
{
	UItemClicker* NewItemClicker = CreateWidget<UItemClicker>( this, ItemClickerClass );

	NewItemClicker->OnClicked.AddDynamic( this, &UInventoryMenu::HandleOnItemClickerClicked );

	WrapBox_ItemClickers->AddChildWrapBox( NewItemClicker );

	return NewItemClicker;
}

void UInventoryMenu::ReloadInventoryDisplay()
{
	if ( !Inventory )
	{
		UE_LOG( LogTemp, Warning, TEXT( "UInventoryMenu.ReloadInventoryDisplay: Inventory is nullptr!" ) );	
		return;
	}

	TArray<AItem*> Items = Inventory->GetItems();

	for ( int i = 0; i < WrapBox_ItemClickers->GetChildrenCount(); i++ )
	{
		/* Get the new ItemWidget. */

		UItemWidget* ItemWidget = nullptr;
		if ( Items.IsValidIndex( i ) )
		{
			ItemWidget = Items[i]->GetItemWidget();
		}

		/* Get the ItemClicker. */

		UItemClicker* ItemClicker = Cast<UItemClicker>( WrapBox_ItemClickers->GetChildAt( i ) );
		if ( !ItemClicker )
		{
			UE_LOG( LogTemp, Error, TEXT( "InventoryMenu's WrapBox_ItemClickers has a non-ItemClicker child!" ) );
			continue;
		}

		/* Reset the content of ItemClicker's ItemWidget NamedSlot. */

		ItemClicker->GetItemWidgetSlot()->ClearChildren();

		if ( ItemWidget )
		{
			ItemClicker->GetItemWidgetSlot()->AddChild( ItemWidget );
		}
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

void UInventoryMenu::HandleOnItemAdded( AItem* ItemAdded )
{
	UE_LOG( LogTemp, Warning, TEXT( "%s is added to inventory." ), *ItemAdded->GetName() );
}

void UInventoryMenu::HandleOnItemRemoved( AItem* ItemRemoved )
{

}
