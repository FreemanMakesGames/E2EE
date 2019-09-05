#pragma once

#include "CoreMinimal.h"
#include "ItemInfo.h"
#include "MessageItemInfo.generated.h"

/**
 * 
 */
UCLASS()
class E2EE_API UMessageItemInfo : public UItemInfo
{
	GENERATED_BODY()

public:

	UMessageItemInfo();

public:

	virtual UMessageItemInfo* Duplicate() override;

	virtual FText Describe() override;

	virtual bool IsEquivalentTo( UItemInfo* OtherItem ) override;
	
};
