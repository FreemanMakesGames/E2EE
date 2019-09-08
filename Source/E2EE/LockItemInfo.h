#pragma once

#include "CoreMinimal.h"
#include "ItemInfo.h"
#include "LockItemInfo.generated.h"

/**
 * 
 */
UCLASS()
class E2EE_API ULockItemInfo : public UItemInfo
{
	GENERATED_BODY()

public:

	ULockItemInfo();

public:

	UFUNCTION( BlueprintCallable )
	FString GetLockId();

	UFUNCTION( BlueprintCallable )
	void SetLockId( FString InLockId );

protected:

	FString LockId;

public:

	virtual ULockItemInfo* Duplicate() override;

	virtual FText Describe() override;

	virtual bool IsEquivalentTo( UItemInfo* OtherItem ) override;
	
};
