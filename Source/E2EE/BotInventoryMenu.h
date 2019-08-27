#pragma once

#include "CoreMinimal.h"
#include "InventoryMenu.h"
#include "BotInventoryMenu.generated.h"

class UContainerItemInfo;

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnPreDuplicationHighlightCompleted );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnContainerOpenHighlightCompleted, UContainerItemInfo*, Container );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnContainerUnlockHighlightCompleted );
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

	void ContainerOpenHighlight( UContainerItemInfo* Container );

	void ContainerUnlockHighlight( UKeyItemInfo* KeyItem, UContainerItemInfo* Container );

	virtual void HideInventory() override;

public:

	UPROPERTY( BlueprintAssignable )
	FOnPreDuplicationHighlightCompleted OnPreDuplicationHighlightCompleted;

	UPROPERTY( BlueprintAssignable )
	FOnContainerOpenHighlightCompleted OnContainerOpenHighlightCompleted;

	UPROPERTY( BlueprintAssignable )
	FOnContainerUnlockHighlightCompleted OnContainerUnlockHighlightCompleted;

	UPROPERTY( BlueprintAssignable )
	FOnHidden OnHidden;

protected:

	UFUNCTION()
	void HandleOnPreDuplicationHighlightCompleted( UItemClicker* HighlightedClicker );

	UFUNCTION()
	void HandleOnContainerOpenHighlightCompleted( UItemClicker* HighlightedClicker );

	UFUNCTION()
	void HandleOnContainerUnlockHighlightCompleted( UItemClicker* HighlightedClicker );
	
};
