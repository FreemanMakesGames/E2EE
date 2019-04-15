#include "Command.h"

#include "Item.h"

void UCommand::Initialize( class AItem* OwnerItem, FString CommandName, bool bRequireSecondaryItem )
{
	this->OwnerItem = OwnerItem;
	this->CommandName = CommandName;
	this->bRequireSecondaryItem = bRequireSecondaryItem;
}

void UCommand::Execute() {}

/* Getters */

FString UCommand::GetCommandName()
{
	return CommandName;
}

bool UCommand::GetRequireSecondItem()
{
	return bRequireSecondaryItem;
}

/* Setters */

void UCommand::SetSecondaryItem( AItem* SecondaryItem )
{
	this->SecondaryItem = SecondaryItem;
}
