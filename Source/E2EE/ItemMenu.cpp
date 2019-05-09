#include "ItemMenu.h"

#include "Item.h"

#include "Components/VerticalBox.h"
#include "Components/Button.h"

UItemMenu::UItemMenu( const FObjectInitializer& ObjectInitializer ) : Super( ObjectInitializer )
{

}

void UItemMenu::NativeOnInitialized()
{
	// Bind UButton events.
	Button_Destroy->OnClicked.AddDynamic( this, &UItemMenu::HandleOnButtonDestroyClicked );
	Button_Drop->OnClicked.AddDynamic( this, &UItemMenu::HandleOnButtonDropClicked );

	// Populate the TMap.
	ItemUsageToButton.Add( EItemUsage::Destroy, Button_Destroy );
	ItemUsageToButton.Add( EItemUsage::Drop, Button_Drop );

	// Clear the UVerticalBox.
	VerticalBox_Buttons->ClearChildren();
}

void UItemMenu::Display( AItem* Item )
{
	CurrentItem = Item;

	VerticalBox_Buttons->ClearChildren();

	for ( EItemUsage ItemUsage : CurrentItem->GetItemUsages() )
	{
		UButton** pButton = ItemUsageToButton.Find( ItemUsage );

		if ( pButton )
		{
			VerticalBox_Buttons->AddChildToVerticalBox( *pButton );
		}
		else
		{
			UE_LOG( LogTemp, Error, TEXT( "UItemMenu found an EItemUsage from an AItem, that doesn't match any UButton in the TMap." ) );
		}
	}
}

void UItemMenu::HandleOnButtonDestroyClicked()
{
	OnButtonDestroyClicked.Broadcast( CurrentItem );
}

void UItemMenu::HandleOnButtonDropClicked()
{
	OnButtonDropClicked.Broadcast( CurrentItem );
}

