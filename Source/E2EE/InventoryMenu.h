#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryMenu.generated.h"

class UItemClicker;
class UInventory;
class UItemWidget;
class UItemInfo;
class UWrapBox;
class UButton;
class UItemMenu;
class UTextBlock;
class UImage;

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnAdditionHighlightCompleted );

/**
 * 
 */
UCLASS( Blueprintable )
class E2EE_API UInventoryMenu : public UUserWidget
{
	GENERATED_BODY()

protected:

 	virtual void NativeOnInitialized() override;

protected:

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	TSubclassOf<UItemClicker> ItemClickerClass;

	UPROPERTY( meta = ( BindWidget ) )
	UWrapBox* WrapBox_ItemClickers;

	UPROPERTY( meta = ( BindWidget ) )
	UTextBlock* TextBlock_Title;

	UPROPERTY( meta = ( BindWidget ) )
	UTextBlock* TextBlock_Description;

	UPROPERTY( meta = (BindWidget) )
	UImage* Image_BlockInput;

	UPROPERTY()
	UInventory* Inventory;

public:

	UFUNCTION( BlueprintCallable )
	void SetupInventory( UInventory* InInventory );

	UFUNCTION( BlueprintCallable )
	void SetupTitle( FText InTitle );

	UFUNCTION( BlueprintCallable )
	void ShowInventory();

	UFUNCTION()
	virtual void HideInventory() PURE_VIRTUAL( , );

public:

	UPROPERTY( BlueprintAssignable )
	FOnAdditionHighlightCompleted OnAdditionHighlightCompleted;

protected:

	UItemClicker* AddNewItemClicker( UItemInfo* Item );

protected:

	UFUNCTION()
	virtual void HandleOnItemClickerClicked( UItemClicker* ClickedItemClicker );

	UFUNCTION()
	void HandleOnClickerAdditionHighlightFinished( UItemClicker* HighlightedClicker );

	UFUNCTION()
	void HandleOnButtonHideInventoryMenuClicked();

	UFUNCTION()
	void HandleOnItemAdded( UItemInfo* ItemAdded );

	UFUNCTION()
	void HandleOnItemRemoved( UItemInfo* ItemRemoved );

protected:

	UFUNCTION( BlueprintCallable )
	virtual void ToggleInput( bool Enabled );

	UFUNCTION( BlueprintCallable )
	void ClearDescription();

protected:

	UPROPERTY( BlueprintReadOnly )
	TMap<UItemInfo*, UItemClicker*> ItemToItemClicker;

	UPROPERTY( BlueprintReadOnly, VisibleAnywhere )
	UItemClicker* LastClickedClicker;

	TArray<UItemClicker*> ClickersPendingForHighlightForAddition;
	
};
