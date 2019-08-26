#include "BotInventoryMenu.h"

#include "ItemClicker.h"
#include "DevUtilities.h"

void UBotInventoryMenu::PreDuplicationHighlight( TArray<UItemInfo*> ItemsToDuplicate )
{
	for ( int i = 0; i < ItemsToDuplicate.Num(); i++ )
	{
		if ( UItemClicker** pItemClicker = ItemToItemClicker.Find( ItemsToDuplicate[i] ) )
		{
			UItemClicker* ItemClicker = *pItemClicker;

			// Only subscribe to 1, instead of all, should be enough.
			if ( i == 0 )
			{
				ItemClicker->OnPreDuplicationHighlightFinished.AddDynamic( this, &UBotInventoryMenu::HandleOnPreDuplicationHighlightCompleted );
			}

			ItemClicker->HighlightForPreDuplication();
		}
		else
		{
			UDevUtilities::PrintError( "UBotInventoryMenu receives a TArray of ItemsToDuplicate, which contains UItemInfo* not found in the TMap ItemToItemClicker." );
		}
	}
}

void UBotInventoryMenu::HideInventory()
{
	Super::HideInventory();

	OnHidden.Broadcast();
}

void UBotInventoryMenu::HandleOnPreDuplicationHighlightCompleted( UItemClicker* HighlightedClicker )
{
	OnPreDuplicationHighlightCompleted.Broadcast();

	HighlightedClicker->OnAdditionHighlightFinished.RemoveDynamic( this, &UBotInventoryMenu::HandleOnPreDuplicationHighlightCompleted );
}
