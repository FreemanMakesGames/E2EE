#include "DestroyCommand.h"

#include "Item.h"

UDestroyCommand::UDestroyCommand()
{
	CommandName = "Destroy";

	bRequireSecondaryItem = false;
}

void UDestroyCommand::Execute()
{
	OwnerItem->Destroy();
}
