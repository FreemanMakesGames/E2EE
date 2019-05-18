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

	UPROPERTY( BlueprintAssignable )
	FOnItemAdded OnItemAdded;

	UPROPERTY( BlueprintAssignable )
	FOnItemRemoved OnItemRemoved;

public:

	UFUNCTION( BlueprintCallable )
	TArray<AItem*> GetItems();

protected:

	UPROPERTY( ReplicatedUsing=OnRep_Items )
	TArray<AItem*> Items;

	UPROPERTY()
	AItem* TempNewItem;

public:

	UFUNCTION( BlueprintCallable )
	int CountItems();

	UFUNCTION( BlueprintCallable )
	void AddItem( AItem* ItemToAdd );

	UFUNCTION()
	void OnRep_Items();

	UFUNCTION( BlueprintCallable )
	void RemoveItem( AItem* ItemToRemove );

	UFUNCTION( BlueprintCallable )
	void DropItem( AItem* ItemToDrop );

	UFUNCTION( Server, Reliable, WithValidation, BlueprintCallable )
	void ServerDuplicateItem( AItem* ItemToDuplicate );

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable )
	void OpenItem( AItem* ItemToOpen );

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable )
	void ReadItem( AItem* ItemToRead );

	UFUNCTION( BlueprintCallable )
	void CombineItems( TArray<AItem*> SourceItems );

	UFUNCTION( BlueprintImplementableEvent )
	TArray<AItem*> CombineItemsWithItemCombiner( const TArray<AItem*>& SourceItems );
	
};
