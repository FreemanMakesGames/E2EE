#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Inventory.generated.h"

class UItemInfo;
class UItemCombiner;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnItemAdded, UItemInfo*, Item );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnItemRemoved, UItemInfo*, Item );

/**
 * 
 */
UCLASS( Blueprintable, BlueprintType, ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent ) )
class E2EE_API UInventory : public UActorComponent
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

public:

	UPROPERTY( BlueprintAssignable )
	FOnItemAdded OnItemAdded;

	UPROPERTY( BlueprintAssignable )
	FOnItemRemoved OnItemRemoved;

public:

	UFUNCTION( BlueprintCallable )
	TArray<UItemInfo*> GetItems();

protected:

	UPROPERTY( VisibleInstanceOnly )
	TArray<UItemInfo*> Items;

	UPROPERTY()
	UItemCombiner* ItemCombiner;

public:

	UFUNCTION( BlueprintCallable )
	int CountItems();

	UFUNCTION( BlueprintCallable )
	void AddItem( UItemInfo* ItemToAdd );

	UFUNCTION( BlueprintCallable )
	void RemoveItem( UItemInfo* ItemToRemove );

	UFUNCTION( BlueprintCallable )
	void DropItem( UItemInfo* ItemToDrop );

	UFUNCTION( Server, Reliable, WithValidation, BlueprintCallable )
	void ServerDuplicateItem( UItemInfo* TargetItem );

	UFUNCTION( NetMulticast, Reliable )
	void MulticastDuplicateItem( UItemInfo* TargetItem );

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable )
	void OpenItem( UItemInfo* ItemToOpen );

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable )
	void ReadItem( UItemInfo* ItemToRead );

	UFUNCTION( BlueprintCallable )
	void CombineItems( TArray<UItemInfo*> SourceItems );
	
};
