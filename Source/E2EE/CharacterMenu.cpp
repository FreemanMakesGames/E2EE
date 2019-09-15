#include "CharacterMenu.h"

#include "BasicCharacter.h"

#include "Components/Button.h"

void UCharacterMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

// 	Button_ViewInventory->OnClicked.AddDynamic( this, &UCharacterMenu::HandleOnButtonViewInventoryClicked );
// 	Button_PickUpItems->OnClicked.AddDynamic( this, &UCharacterMenu::HandleOnButtonPickUpItemsClicked );
// 	Button_SendItems->OnClicked.AddDynamic( this, &UCharacterMenu::HandleOnButtonSendItemsClicked );
// 	Button_Back->OnClicked.AddDynamic( this, &UCharacterMenu::HandleOnButtonBackClicked );
}

void UCharacterMenu::SetOwnerCharacter( ABasicCharacter* InOwnerCharacter )
{
	ensureAlways( !OwnerCharacter );

	OwnerCharacter = InOwnerCharacter;
}

void UCharacterMenu::HandleOnButtonViewInventoryClicked()
{
	OwnerCharacter->ShowInventory();
}

void UCharacterMenu::HandleOnButtonPickUpItemsClicked()
{
	OwnerCharacter->PickUpItems();
}

void UCharacterMenu::HandleOnButtonSendItemsClicked()
{
	OwnerCharacter->SendItems();
}

void UCharacterMenu::HandleOnButtonBackClicked()
{
	OwnerCharacter->Unfocus();
}
