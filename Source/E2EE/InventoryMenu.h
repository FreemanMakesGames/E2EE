#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryMenu.generated.h"

class UItemClicker;
class UInventory;
class AItem;
class UWrapBox;
class UButton;

/**
 * 
 */
UCLASS()
class E2EE_API UInventoryMenu : public UUserWidget
{
	GENERATED_BODY()

protected:

 	virtual void NativeOnInitialized() override;

public:

	UFUNCTION( BlueprintCallable )
	UInventory* GetInventory();

	UFUNCTION( BlueprintCallable )
	void SetInventory( UInventory* InventoryToSet );

protected:

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	TSubclassOf<UItemClicker> ItemClickerClass;

	UPROPERTY()
	TMap<AItem*, UItemClicker*> ItemToItemClicker;

	UPROPERTY( meta = ( BindWidget ) )
	UWrapBox* WrapBox_ItemClickers;

	UPROPERTY( meta = ( BindWidget ) )
	UButton* Button_HideInventoryMenu;

	UPROPERTY()
	UInventory* Inventory;

	UPROPERTY( EditDefaultsOnly )
	int MaxItemSlots;

protected:

	UItemClicker* AddNewItemClicker();

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
