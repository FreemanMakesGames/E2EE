// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Inventory.generated.h"

class AItem;

/**
 * 
 */
UCLASS( BlueprintType, ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent ) )
class E2EE_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:

	TArray<AItem*> GetItems();

	UFUNCTION( BlueprintCallable )
	void AddItem( AItem* ItemToAdd );

	UFUNCTION( BlueprintCallable )
	void RemoveItem( AItem* ItemToRemove );

	UFUNCTION( BlueprintCallable )
	int CountItems();

protected:

	UPROPERTY()
	TArray<AItem*> Items;
	
};
