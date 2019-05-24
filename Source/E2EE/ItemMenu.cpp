#include "ItemMenu.h"

#include "ItemInfo.h"

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
	Button_Duplicate->OnClicked.AddDynamic( this, &UItemMenu::HandleOnButtonDuplicateClicked );
	Button_Open->OnClicked.AddDynamic( this, &UItemMenu::HandleOnButtonOpenClicked );
	Button_Read->OnClicked.AddDynamic( this, &UItemMenu::HandleOnButtonReadClicked );

	// Bind UButton events for Item combinations.
	Button_Lock->OnClicked.AddDynamic( this, &UItemMenu::HandleOnButtonForCombinationClicked );
	Button_Unlock->OnClicked.AddDynamic( this, &UItemMenu::HandleOnButtonForCombinationClicked );
	Button_Contain->OnClicked.AddDynamic( this, &UItemMenu::HandleOnButtonForCombinationClicked );

	// Populate the TMap.
	ItemUsageToButton.Add( EItemUsage::Destroy, Button_Destroy );
	ItemUsageToButton.Add( EItemUsage::Drop, Button_Drop );
	ItemUsageToButton.Add( EItemUsage::Duplicate, Button_Duplicate );
	ItemUsageToButton.Add( EItemUsage::Lock, Button_Lock );
	ItemUsageToButton.Add( EItemUsage::Unlock, Button_Unlock );
	ItemUsageToButton.Add( EItemUsage::Open, Button_Open );
	ItemUsageToButton.Add( EItemUsage::Read, Button_Read );
	ItemUsageToButton.Add( EItemUsage::Contain, Button_Contain );

	// Clear the UVerticalBox.
	VerticalBox_Buttons->ClearChildren();
}

void UItemMenu::Display( UItemInfo* Item )
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
			UE_LOG( LogTemp, Error, TEXT( "UItemMenu found an EItemUsage from a UItemInfo, that doesn't match any UButton in the TMap." ) );
		}
	}
}

#pragma region Button event handlers
void UItemMenu::HandleOnButtonDestroyClicked()
{
	OnButtonDestroyClicked.Broadcast( CurrentItem );

	VerticalBox_Buttons->ClearChildren();
}

void UItemMenu::HandleOnButtonDropClicked()
{
	OnButtonDropClicked.Broadcast( CurrentItem );

	VerticalBox_Buttons->ClearChildren();
}

void UItemMenu::HandleOnButtonDuplicateClicked()
{
	OnButtonDuplicateClicked.Broadcast( CurrentItem );

	VerticalBox_Buttons->ClearChildren();
}

void UItemMenu::HandleOnButtonOpenClicked()
{
	OnButtonOpenClicked.Broadcast( CurrentItem );

	VerticalBox_Buttons->ClearChildren();
}

void UItemMenu::HandleOnButtonReadClicked()
{
	OnButtonReadClicked.Broadcast( CurrentItem );

	VerticalBox_Buttons->ClearChildren();
}

void UItemMenu::HandleOnButtonForCombinationClicked()
{
	OnButtonForCombinationClicked.Broadcast( CurrentItem );

	VerticalBox_Buttons->ClearChildren();
}
#pragma endregion
