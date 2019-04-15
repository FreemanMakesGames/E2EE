#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Command.generated.h"

class AItem;

/**
 * 
 */
UCLASS()
class E2EE_API UCommand : public UObject
{
	GENERATED_BODY()

public:

	void Initialize( AItem* OwnerItem, FString CommandName, bool bRequireSecondaryItem );

	virtual void Execute();

	// Getters
	FString GetCommandName();
	bool GetRequireSecondItem();

	// Setters
	void SetSecondaryItem( AItem* SecondaryItem );

protected:

	AItem* OwnerItem;

	FString CommandName;

	bool bRequireSecondaryItem;

	AItem* SecondaryItem;
	
};
