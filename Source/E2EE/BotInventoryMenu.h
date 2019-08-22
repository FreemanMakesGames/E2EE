#pragma once

#include "CoreMinimal.h"
#include "InventoryMenu.h"
#include "BotInventoryMenu.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnHidden );

/**
 * 
 */
UCLASS()
class E2EE_API UBotInventoryMenu : public UInventoryMenu
{
	GENERATED_BODY()

public:

	virtual void HideInventory() override;

public:

	UPROPERTY( BlueprintAssignable )
	FOnHidden OnHidden;
	
};
