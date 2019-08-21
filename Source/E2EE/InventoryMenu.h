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

	UPROPERTY()
	TMap<UItemInfo*, UItemClicker*> ItemToItemClicker;

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

	UFUNCTION( BlueprintCallable )
	void HideInventory();

protected:

	UItemClicker* AddNewItemClicker( UItemInfo* Item );

	void ReloadInventoryDisplay();

#pragma region My UI event handlers
	UFUNCTION()
	void HandleOnItemClickerClicked( UItemClicker* ClickedItemClicker );

	UFUNCTION()
	void HandleOnButtonHideInventoryMenuClicked();
#pragma endregion

#pragma region Item Menu event handlers
	UFUNCTION()
	void HandleOnItemMenuButtonDestroyClicked( UItemInfo* TargetItem );

	UFUNCTION()
	void HandleOnItemMenuButtonDropClicked( UItemInfo* TargetItem );

	UFUNCTION()
	void HandleOnItemMenuButtonDuplicateClicked( UItemInfo* TargetItem );

	UFUNCTION()
	void HandleOnItemMenuButtonOpenClicked( UItemInfo* TargetItem );

	UFUNCTION()
	void HandleOnItemMenuButtonReadClicked( UItemInfo* TargetItem );

	UFUNCTION()
	void HandleOnItemMenuButtonForCombinationClicked( UItemInfo* TargetItem );
#pragma endregion

#pragma region Inventory event handlers
	UFUNCTION()
	void HandleOnItemAdded( UItemInfo* ItemAdded );

	UFUNCTION()
	void HandleOnItemRemoved( UItemInfo* ItemRemoved );
#pragma endregion

protected:

	UPROPERTY( VisibleAnywhere )
	UItemInfo* FirstItemForCombination;

	UPROPERTY( BlueprintReadOnly, VisibleAnywhere )
	bool bIsCombining;

	UPROPERTY( BlueprintReadOnly, VisibleAnywhere )
	UItemClicker* LastClickedClicker;
	
};
