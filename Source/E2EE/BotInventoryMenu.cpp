#include "BotInventoryMenu.h"

#include "ItemClicker.h"
#include "ContainerItemInfo.h"
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
		else { ensureAlways( false ); }
	}
}

void UBotInventoryMenu::ContainerOpenHighlight( UContainerItemInfo* Container )
{
	if ( UItemClicker** pItemClicker = ItemToItemClicker.Find( Container ) )
	{
		( *pItemClicker )->OnContainerOpenHighlightFinished.AddDynamic( this, &UBotInventoryMenu::HandleOnContainerOpenHighlightCompleted );

		( *pItemClicker )->HighlightForContainerOpen();
	}
	else { ensureAlways( false ); }
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

void UBotInventoryMenu::HandleOnContainerOpenHighlightCompleted( UItemClicker* HighlightedClicker )
{
	OnContainerOpenHighlightCompleted.Broadcast( Cast<UContainerItemInfo>( HighlightedClicker->GetItemInfo() ) );

	HighlightedClicker->OnContainerOpenHighlightFinished.RemoveDynamic( this, &UBotInventoryMenu::HandleOnContainerOpenHighlightCompleted );
}
