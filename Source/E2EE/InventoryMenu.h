// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryMenu.generated.h"

class UInventory;
class UItemClicker;
class UWrapBox;

/**
 * 
 */
UCLASS()
class E2EE_API UInventoryMenu : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION( BlueprintCallable )
	UInventory* GetInventory();

	UFUNCTION( BlueprintCallable )
	void SetInventory( UInventory* InventoryToSet );

protected:

 	virtual void NativeOnInitialized() override;

	void ReloadDisplay();

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	TSubclassOf<UItemClicker> ItemClickerClass;

	UPROPERTY()
	UInventory* Inventory;

	UPROPERTY( meta = ( BindWidget ) )
	UWrapBox* WrapBox_ItemClickers;
	
};
