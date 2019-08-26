#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemClicker.generated.h"

class UItemInfo;
class UItemWidget;
class UButton;
class UNamedSlot;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnButtonClickerClicked, UItemClicker*, ClickedItemClicker );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnAdditionHighlightFinished, UItemClicker*, HighlightedClicker );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnPreDuplicationHighlightFinished, UItemClicker*, HighlightedClicker );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnContainerOpenHighlightFinished, UItemClicker*, HighlightedClicker );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnContainerUnlockHighlightFinished, UItemClicker*, HighlightedClicker );

/**
 * 
 */
UCLASS()
class E2EE_API UItemClicker : public UUserWidget
{
	GENERATED_BODY()

public:

	UItemClicker( const FObjectInitializer& ObjectInitializer );

protected:

	virtual void NativeOnInitialized() override;

public:

	UPROPERTY( BlueprintAssignable  )
	FOnButtonClickerClicked OnClicked;

	UPROPERTY( BlueprintAssignable, BlueprintCallable )
	FOnAdditionHighlightFinished OnAdditionHighlightFinished;

	UPROPERTY( BlueprintAssignable, BlueprintCallable )
	FOnContainerOpenHighlightFinished OnContainerOpenHighlightFinished;

	UPROPERTY( BlueprintAssignable, BlueprintCallable )
	FOnContainerUnlockHighlightFinished OnContainerUnlockHighlightFinished;

	UPROPERTY( BlueprintAssignable, BlueprintCallable )
	FOnPreDuplicationHighlightFinished OnPreDuplicationHighlightFinished;

public:

	UFUNCTION( BlueprintCallable )
	UItemInfo* GetItemInfo();

	UFUNCTION( BlueprintCallable )
	void SetItemInfo( UItemInfo* ItemToSet );

protected:

	UPROPERTY( meta = ( BindWidget ), BlueprintReadOnly )
	UButton* Button_Clicker;

	UPROPERTY( meta = ( BindWidget ) )
	UNamedSlot* NamedSlot_ItemWidgetSlot;

	UPROPERTY( BlueprintReadWrite )
	UItemInfo* ItemInfo;

protected:

	UFUNCTION()
	void HandleOnButtonClicked();

#pragma region Aesthetics
public:

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable )
	void Unhighlight();

	/**
	 * This should be called from UInventoryMenu,
	 * When it's clicked, and it's not combining.
	 */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable )
	void HighlightForClicking();

	/** This is called from UInventoryMenu. */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable )
	void HighlightForItemAddition();

	/** This is called from UInventoryMenu. */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable )
	void HighlightForPreDuplication();

	/** This is called from UInventoryMenu. */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable )
	void HighlightForContainerOpen();

	/** This is called from UInventoryMenu. */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable )
	void HighlightForContainerUnlock();

#pragma endregion
	
};
