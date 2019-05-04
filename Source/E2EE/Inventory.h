#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Inventory.generated.h"

class AItem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnItemAddedEvent, AItem*, Item );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnItemRemovedEvent, AItem*, Item );

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

	UPROPERTY( BlueprintAssignable )
	FOnItemAddedEvent OnItemAdded;

	UPROPERTY( BlueprintAssignable )
	FOnItemRemovedEvent OnItemRemoved;

protected:

	UPROPERTY()
	TArray<AItem*> Items;
	
};
