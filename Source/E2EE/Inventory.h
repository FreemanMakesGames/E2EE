// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Inventory.generated.h"

class AItem;

/**
 * 
 */
UCLASS()
class E2EE_API UInventory : public UObject
{
	GENERATED_BODY()

public:

	void AddItem( AItem* ItemToAdd );

	void RemoveItem( AItem* ItemToRemove );

protected:

	UPROPERTY()
	TArray<AItem*> Items;
	
};
