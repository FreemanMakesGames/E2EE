#include "BasicGameState.h"

#include "ItemDefinitionList.h"
#include "Lock.h"
#include "KeyItem.h"

AItemDefinitionList* ABasicGameState::GetItemDefinitionList()
{
	return ItemDefinitionList;
}

void ABasicGameState::SetIdForKeyPair( ALock* InLock, AKeyItem* InKey )
{
	InLock->SetLockId( NextUsableKeyPairId );
	InKey->SetKeyId( NextUsableKeyPairId );

	IncrementUsableKeyPairId();
}

void ABasicGameState::IncrementUsableKeyPairId()
{
	NextUsableKeyPairId++;
}
