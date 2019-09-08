#pragma once

#include "CoreMinimal.h"
#include "InventoryMenu.h"
#include "BotInventoryMenu.generated.h"

class UContainerItemInfo;

class UButton;

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnPreDuplicationHighlightCompleted );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnContainerOpenHighlightCompleted, UContainerItemInfo*, Container );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnContainerUnlockHighlightCompleted );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnProceed );

/**
 * 
 */
UCLASS()
class E2EE_API UBotInventoryMenu : public UInventoryMenu
{
	GENERATED_BODY()

protected:

	virtual void NativeOnInitialized() override;

protected:

	UPROPERTY( meta = ( BindWidget ) )
	UWrapBox* WrapBox_ItemClickersForDelivery;

public:

	void SetupItemClickersForDelivery( TArray<UItemInfo*> ItemsToDeliver );

	void ClearItemClickersForDelivery( TArray<UItemInfo*> ItemsToDeliver );

	void PreDuplicationHighlight( TArray<UItemInfo*> ItemsToDuplicate );

	void ContainerOpenHighlight( UContainerItemInfo* Container );

	void ContainerUnlockHighlight( UKeyItemInfo* KeyItem, UContainerItemInfo* Container );

public:

	UPROPERTY( BlueprintAssignable )
	FOnPreDuplicationHighlightCompleted OnPreDuplicationHighlightCompleted;

	UPROPERTY( BlueprintAssignable )
	FOnContainerOpenHighlightCompleted OnContainerOpenHighlightCompleted;

	UPROPERTY( BlueprintAssignable )
	FOnContainerUnlockHighlightCompleted OnContainerUnlockHighlightCompleted;

	UPROPERTY( BlueprintAssignable )
	FOnProceed OnProceed;

protected:

	UPROPERTY( meta = ( BindWidget ) )
	UButton* Button_Proceed;

protected:

	virtual void HandleOnItemClickerClicked( UItemClicker* ClickedItemClicker ) override;

	UFUNCTION()
	void HandleOnPreDuplicationHighlightCompleted( UItemClicker* HighlightedClicker );

	UFUNCTION()
	void HandleOnContainerOpenHighlightCompleted( UItemClicker* HighlightedClicker );

	UFUNCTION()
	void HandleOnContainerUnlockHighlightCompleted( UItemClicker* HighlightedClicker );

	UFUNCTION()
	void HandleOnDeliveryItemClickerAdditionHighlightDone( UItemClicker* HighlightedClicker );

	UFUNCTION()
	void HandleOnButtonProceedClicked();
	
};
