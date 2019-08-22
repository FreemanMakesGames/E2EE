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
	UItemMenu* ItemMenu;

	UPROPERTY( meta = ( BindWidget ) )
	UWrapBox* WrapBox_ItemClickers;

	UPROPERTY( meta = ( BindWidget ) )
	UButton* Button_HideInventoryMenu;

	UPROPERTY()
	UInventory* Inventory;

public:

	UFUNCTION( BlueprintCallable )
	void SetupInventory( UInventory* InInventory );

	UFUNCTION( BlueprintCallable )
	void ShowInventory();

	UFUNCTION( BlueprintCallable )
	virtual void HideInventory();

protected:

	UItemClicker* AddNewItemClicker( UItemInfo* Item );

protected:

	UFUNCTION()
	virtual void HandleOnItemClickerClicked( UItemClicker* ClickedItemClicker );

	UFUNCTION()
	void HandleOnButtonHideInventoryMenuClicked();

	UFUNCTION()
	void HandleOnItemAdded( UItemInfo* ItemAdded );

	UFUNCTION()
	void HandleOnItemRemoved( UItemInfo* ItemRemoved );

protected:

	UPROPERTY()
	TMap<UItemInfo*, UItemClicker*> ItemToItemClicker;

	UPROPERTY( VisibleAnywhere )
	UItemInfo* FirstItemForCombination;

	UPROPERTY( BlueprintReadOnly, VisibleAnywhere )
	bool bIsCombining;

	UPROPERTY( BlueprintReadOnly, VisibleAnywhere )
	UItemClicker* LastClickedClicker;

	TArray<UItemClicker*> ClickersPendingForHighlightForAddition;
	
};
