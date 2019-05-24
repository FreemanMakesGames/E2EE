#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Message.generated.h"

class UMessageItemInfo;

/**
 * 
 */
UCLASS()
class E2EE_API AMessage : public AItem
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

public:

	virtual UItemInfo* GetItemInfo() override;

protected:

	UPROPERTY()
	UMessageItemInfo* MessageItemInfo;
	
};
