#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Inventory.generated.h"

class AItem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnItemAdded, AItem*, Item );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnItemRemoved, AItem*, Item );

/**
 * 
 */
UCLASS( Blueprintable, BlueprintType, ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent ) )
class E2EE_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:

	TArray<AItem*> GetItems();

	UFUNCTION( BlueprintCallable )
	int CountItems();

	UFUNCTION( BlueprintCallable )
	void AddItem( AItem* ItemToAdd );

	UFUNCTION( BlueprintCallable )
	void RemoveItem( AItem* ItemToRemove );

	UFUNCTION( BlueprintCallable )
	void DropItem( AItem* ItemToDrop );

	UFUNCTION( BlueprintCallable )
	void CombineItems( AItem* Item1, AItem* Item2 );

	UFUNCTION( BlueprintImplementableEvent )
	TArray<AItem*> CombineItemsWithItemCombiner( AItem* Item1, AItem* Item2 );

	UPROPERTY( BlueprintAssignable )
	FOnItemAdded OnItemAdded;

	UPROPERTY( BlueprintAssignable )
	FOnItemRemoved OnItemRemoved;

protected:

	UPROPERTY()
	TArray<AItem*> Items;
	
};
