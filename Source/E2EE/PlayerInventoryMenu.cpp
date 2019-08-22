#include "PlayerInventoryMenu.h"

#include "Inventory.h"
#include "ItemClicker.h"
#include "ItemMenu.h"

void UPlayerInventoryMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// Bind UItemMenu events.
	ItemMenu->OnButtonDestroyClicked.AddDynamic( this, &UPlayerInventoryMenu::HandleOnItemMenuButtonDestroyClicked );
	ItemMenu->OnButtonDropClicked.AddDynamic( this, &UPlayerInventoryMenu::HandleOnItemMenuButtonDropClicked );
	ItemMenu->OnButtonDuplicateClicked.AddDynamic( this, &UPlayerInventoryMenu::HandleOnItemMenuButtonDuplicateClicked );
	ItemMenu->OnButtonOpenClicked.AddDynamic( this, &UPlayerInventoryMenu::HandleOnItemMenuButtonOpenClicked );
	ItemMenu->OnButtonReadClicked.AddDynamic( this, &UPlayerInventoryMenu::HandleOnItemMenuButtonReadClicked );
	ItemMenu->OnButtonForCombinationClicked.AddDynamic( this, &UPlayerInventoryMenu::HandleOnItemMenuButtonForCombinationClicked );
}

#pragma region Item Menu event handlers
void UPlayerInventoryMenu::HandleOnItemClickerClicked( UItemClicker* ClickedItemClicker )
{
	UItemInfo* TargetItem = ClickedItemClicker->GetItemInfo();

	if ( bIsCombining )
	{
		TArray<UItemInfo*> CombiningItems;
		CombiningItems.Add( FirstItemForCombination );
		CombiningItems.Add( TargetItem );

		Inventory->CombineItems( CombiningItems );

		bIsCombining = false;

		if ( LastClickedClicker ) LastClickedClicker->Unhighlight();
		if ( ClickedItemClicker ) ClickedItemClicker->Unhighlight();
	}
	else
	{
		ItemMenu->Display( TargetItem );

		FirstItemForCombination = TargetItem;

		if ( LastClickedClicker ) LastClickedClicker->Unhighlight();
		ClickedItemClicker->HighlightForClicking();
	}

	LastClickedClicker = ClickedItemClicker;
}

void UPlayerInventoryMenu::HandleOnItemMenuButtonDestroyClicked( UItemInfo* TargetItem )
{
	Inventory->RemoveItem( TargetItem );
}

void UPlayerInventoryMenu::HandleOnItemMenuButtonDropClicked( UItemInfo* TargetItem )
{
	Inventory->DropItem( TargetItem );
}

void UPlayerInventoryMenu::HandleOnItemMenuButtonDuplicateClicked( UItemInfo* TargetItem )
{
	Inventory->ServerDuplicateItem( TargetItem );
}

void UPlayerInventoryMenu::HandleOnItemMenuButtonOpenClicked( UItemInfo* TargetItem )
{
	Inventory->OpenItem( TargetItem );
}

void UPlayerInventoryMenu::HandleOnItemMenuButtonReadClicked( UItemInfo* TargetItem )
{
	Inventory->ReadItem( TargetItem );
}

void UPlayerInventoryMenu::HandleOnItemMenuButtonForCombinationClicked( UItemInfo* TargetItem )
{
	bIsCombining = true;
}
#pragma endregion
