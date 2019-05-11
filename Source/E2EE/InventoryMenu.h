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

#pragma region My UI event handlers
	UFUNCTION()
	void HandleOnItemClickerClicked( UItemClicker* ClickedItemClicker );

	UFUNCTION()
	void HandleOnButtonHideInventoryMenuClicked();
#pragma endregion

#pragma region Item Menu event handlers
	UFUNCTION()
	void HandleOnItemMenuButtonDestroyClicked( AItem* TargetItem );

	UFUNCTION()
	void HandleOnItemMenuButtonDropClicked( AItem* TargetItem );

	UFUNCTION()
	void HandleOnItemMenuButtonOpenClicked( AItem* TargetItem );

	UFUNCTION()
	void HandleOnItemMenuButtonForCombinationClicked( AItem* TargetItem );
#pragma endregion

#pragma region Inventory event handlers
	UFUNCTION()
	void HandleOnItemAdded( AItem* ItemAdded );

	UFUNCTION()
	void HandleOnItemRemoved( AItem* ItemRemoved );
#pragma endregion

protected:

	UPROPERTY( VisibleAnywhere )
	AItem* FirstItemForCombination;

	UPROPERTY( VisibleAnywhere )
	bool bIsCombining;
	
};
