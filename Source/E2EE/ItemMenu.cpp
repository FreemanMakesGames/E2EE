#include "ItemMenu.h"

#include "Item.h"

#include "Components/VerticalBox.h"
#include "Components/Button.h"

UItemMenu::UItemMenu( const FObjectInitializer& ObjectInitializer ) : Super( ObjectInitializer )
{

}

void UItemMenu::NativeOnInitialized()
{
	ItemUsageToButton.Add( EItemUsage::Destroy, Button_Destroy );
	ItemUsageToButton.Add( EItemUsage::Drop, Button_Drop );

	VerticalBox_Buttons->ClearChildren();
}

void UItemMenu::ShowButtons( AItem* Item )
{
	VerticalBox_Buttons->ClearChildren();

	for ( EItemUsage ItemUsage : Item->GetItemUsages() )
	{
		UButton* Button = *ItemUsageToButton.Find( ItemUsage );

		if ( Button )
		{
			VerticalBox_Buttons->AddChildToVerticalBox( Button );
		}
		else
		{
			UE_LOG( LogTemp, Error, TEXT( "UItemMenu found an EItemUsage from an AItem, that doesn't match any UButton in the TMap." ) );
		}
	}
}

