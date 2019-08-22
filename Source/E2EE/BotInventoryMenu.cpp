#include "BotInventoryMenu.h"

void UBotInventoryMenu::HideInventory()
{
	Super::HideInventory();

	OnHidden.Broadcast();
}
