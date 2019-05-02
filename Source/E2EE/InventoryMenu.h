// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryMenu.generated.h"

class UInventory;
class UItemClicker;
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

	UPROPERTY( meta = ( BindWidget ) )
	UWrapBox* WrapBox_ItemClickers;

	UPROPERTY( meta = ( BindWidget ) )
	UButton* Button_HideInventoryMenu;

	UPROPERTY()
	UInventory* Inventory;

protected:

	void ReloadDisplay();

	UFUNCTION()
	void HandleOnItemClickerClicked( UItemClicker* ClickedItemClicker );

	UFUNCTION()
	void HandleOnButtonHideInventoryMenuClicked();
	
};
