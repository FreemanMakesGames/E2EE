#include "BasicGameState.h"

#include "ItemDefinitionList.h"
#include "LockItemInfo.h"
#include "KeyItemInfo.h"

#include "Engine/World.h"

void ABasicGameState::SetIdForKeyPair( ULockItemInfo* InLock, UKeyItemInfo* InKey )
{
	InLock->SetLockId( NextUsableKeyPairId );
	InKey->SetKeyId( NextUsableKeyPairId );

	IncrementUsableKeyPairId();
}

void ABasicGameState::IncrementUsableKeyPairId()
{
	NextUsableKeyPairId++;
}
