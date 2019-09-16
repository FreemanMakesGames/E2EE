#include "PlayableCharacterMenu.h"

#include "BasicCharacter.h"
#include "DevUtilities.h"

#include "Components/Button.h"

void UPlayableCharacterMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// FFS This has to be OnPressed, because OnClicked won't work. Known bug.
	Button_ViewInventory->OnPressed.AddDynamic( this, &UPlayableCharacterMenu::HandleOnButtonViewInventoryClicked );
	Button_PickUpItems->OnPressed.AddDynamic( this, &UPlayableCharacterMenu::HandleOnButtonPickUpItemsClicked );
	Button_SendItems->OnPressed.AddDynamic( this, &UPlayableCharacterMenu::HandleOnButtonSendItemsClicked );
	Button_Back->OnPressed.AddDynamic( this, &UPlayableCharacterMenu::HandleOnButtonBackClicked );
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
