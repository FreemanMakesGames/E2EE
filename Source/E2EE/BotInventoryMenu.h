#pragma once

#include "CoreMinimal.h"
#include "InventoryMenu.h"
#include "BotInventoryMenu.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnPreDuplicationHighlightCompleted );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnHidden );

/**
 * 
 */
UCLASS()
class E2EE_API UBotInventoryMenu : public UInventoryMenu
{
	GENERATED_BODY()

public:

	void PreDuplicationHighlight( TArray<UItemInfo*> ItemsToDuplicate );

	virtual void HideInventory() override;

public:

	UPROPERTY( BlueprintAssignable )
	FOnPreDuplicationHighlightCompleted OnPreDuplicationHighlightCompleted;

	UPROPERTY( BlueprintAssignable )
	FOnHidden OnHidden;

protected:

	UFUNCTION()
	void HandleOnPreDuplicationHighlightCompleted( UItemClicker* HighlightedClicker );
	
};
