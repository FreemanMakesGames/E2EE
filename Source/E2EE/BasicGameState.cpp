#include "BasicGameState.h"

#include "ItemDefinitionList.h"

AItemDefinitionList* ABasicGameState::GetItemDefinitionList()
{
	return ItemDefinitionList;
}

void ABasicGameState::IncrementUsableKeyPairId()
{
	NextUsableKeyPairId++;
}
