#include "PlayableCharacterMenu.h"

#include "BasicCharacter.h"

#include "Components/Button.h"

void UPlayableCharacterMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Button_ViewInventory->OnClicked.AddDynamic( this, &UPlayableCharacterMenu::HandleOnButtonViewInventoryClicked );
	Button_PickUpItems->OnClicked.AddDynamic( this, &UPlayableCharacterMenu::HandleOnButtonPickUpItemsClicked );
	Button_SendItems->OnClicked.AddDynamic( this, &UPlayableCharacterMenu::HandleOnButtonSendItemsClicked );
	Button_Back->OnClicked.AddDynamic( this, &UPlayableCharacterMenu::HandleOnButtonBackClicked );
}

void UPlayableCharacterMenu::SetOwnerCharacter( ABasicCharacter* InOwnerCharacter )
{
	ensureAlways( !OwnerCharacter );

	OwnerCharacter = InOwnerCharacter;
}

void UPlayableCharacterMenu::HandleOnButtonViewInventoryClicked()
{
	OwnerCharacter->ShowInventory();
}

void UPlayableCharacterMenu::HandleOnButtonPickUpItemsClicked()
{
	OwnerCharacter->PickUpItems();
}

void UPlayableCharacterMenu::HandleOnButtonSendItemsClicked()
{
	OwnerCharacter->SendItems();
}

void UPlayableCharacterMenu::HandleOnButtonBackClicked()
{
	OwnerCharacter->Unfocus();
}
