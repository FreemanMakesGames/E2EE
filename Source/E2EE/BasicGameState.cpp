#include "BasicGameState.h"

#include "ItemDefinitionList.h"
#include "Lock.h"
#include "KeyItem.h"

#include "Engine/World.h"

void ABasicGameState::BeginPlay()
{
	ItemDefinitionList = GetWorld()->SpawnActor<AItemDefinitionList>( FVector::ZeroVector, FRotator::ZeroRotator );
}

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
