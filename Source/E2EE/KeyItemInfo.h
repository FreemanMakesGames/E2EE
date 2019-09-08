#pragma once

#include "CoreMinimal.h"
#include "ItemInfo.h"
#include "KeyItemInfo.generated.h"

/**
 *
 */
UCLASS()
class E2EE_API UKeyItemInfo : public UItemInfo
{
	GENERATED_BODY()

public:

	UKeyItemInfo();

public:

	UFUNCTION( BlueprintCallable )
	FString GetKeyId();

	UFUNCTION( BlueprintCallable )
	void SetKeyId( FString InKeyId );

protected:

	FString KeyId;

public:

	virtual UKeyItemInfo* Duplicate() override;

	virtual FText Describe() override;

	virtual bool IsEquivalentTo( UItemInfo* OtherItem ) override;

};
