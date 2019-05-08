#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryMenu.generated.h"

class UItemClicker;
class UInventory;
class UItemWidget;
class AItem;
class UWrapBox;
class UButton;
class UItemMenu;

/**
 * 
 */
UCLASS()
class E2EE_API UInventoryMenu : public UUserWidget
{
	GENERATED_BODY()

protected:

 	virtual void NativeOnInitialized() override;

protected:

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	TSubclassOf<UItemClicker> ItemClickerClass;

	UPROPERTY()
	TMap<AItem*, UItemClicker*> ItemToItemClicker;

	UPROPERTY( meta = ( BindWidget ) )
	UWrapBox* WrapBox_ItemClickers;

	UPROPERTY( meta = ( BindWidget ) )
	UItemMenu* ItemMenu;

	UPROPERTY( meta = ( BindWidget ) )
	UButton* Button_HideInventoryMenu;

	UPROPERTY()
	UInventory* Inventory;

public:

	UFUNCTION( BlueprintCallable )
	void ShowInventory( UInventory* InventoryToSet );

protected:

	UItemClicker* AddNewItemClicker( AItem* Item );

	void ReloadInventoryDisplay();

	UFUNCTION()
	void HandleOnItemClickerClicked( UItemClicker* ClickedItemClicker );

	UFUNCTION()
	void HandleOnButtonHideInventoryMenuClicked();

	UFUNCTION()
	void HandleOnItemAdded( AItem* ItemAdded );

	UFUNCTION()
	void HandleOnItemRemoved( AItem* ItemRemoved );
	
};
