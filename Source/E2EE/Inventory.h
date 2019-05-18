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

	UFUNCTION( NetMulticast, Reliable, BlueprintCallable )
	void AddItem( AItem* ItemToAdd );

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
	void CombineItems( TArray<AItem*> Items );

	UFUNCTION( BlueprintImplementableEvent )
	TArray<AItem*> CombineItemsWithItemCombiner( const TArray<AItem*>& SourceItems );

	UPROPERTY( BlueprintAssignable )
	FOnItemAdded OnItemAdded;

	UPROPERTY( BlueprintAssignable )
	FOnItemRemoved OnItemRemoved;

protected:

	UFUNCTION( Client, Reliable )
	void ClientReceiveDuplicatedItem( AItem* Clone );

protected:

	UPROPERTY()
	TArray<AItem*> Items;
	
};
