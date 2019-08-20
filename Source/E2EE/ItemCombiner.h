#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemCombiner.generated.h"

class AItem;
class UItemInfo;
class ABasicPlayerController;

// FIXME: Item Combination: TMap can't handle this struct as key properly. 
USTRUCT()
struct FArrayOfItemTypeId
{
	GENERATED_BODY()

public:

	FArrayOfItemTypeId() {}

	FArrayOfItemTypeId( TArray<int> InItemTypeIds )
	{
		ItemTypeIds = InItemTypeIds;
	}

	UPROPERTY()
	TArray<int> ItemTypeIds;

	bool operator==( const FArrayOfItemTypeId& Other ) const
	{
		return ItemTypeIds == Other.ItemTypeIds;
	}
};

FORCEINLINE uint32 GetTypeHash( const FArrayOfItemTypeId& ArrayOfItems )
{
	return FCrc::MemCrc_DEPRECATED( &ArrayOfItems, sizeof( FArrayOfItemTypeId ) );
}

USTRUCT( BlueprintType )
struct FItemCombinationResult
{
	GENERATED_BODY()

public:

	FItemCombinationResult() {}

	FItemCombinationResult( bool InSuccessful, TArray<UItemInfo*> InResultItems )
	{
		Successful = InSuccessful;
		ResultItems = InResultItems;
	}

	UPROPERTY()
		bool Successful;

	UPROPERTY()
		TArray<UItemInfo*> ResultItems;
};

/**
 * 
 */
UCLASS( BlueprintType )
class E2EE_API UItemCombiner : public UObject
{
	GENERATED_BODY()

public:

	typedef TArray<UItemInfo*>( UItemCombiner::*FCombineFunction )( TArray <UItemInfo*> );

public:

	UItemCombiner();

public:

	void SetPlayerController( ABasicPlayerController* InPlayerController );

protected:

	// Player controller for notifications
	ABasicPlayerController* PlayerController;

protected:

	TMap<FArrayOfItemTypeId, FCombineFunction> FunctionMap;

	TMap<int, FCombineFunction> FunctionMapForWildCards;

public:

	UFUNCTION( BlueprintCallable )
	FItemCombinationResult CombineItems( TArray<UItemInfo*> SourceItems );

protected:

	UFUNCTION( BlueprintCallable )
	TArray<UItemInfo*> LockContainer( TArray<UItemInfo*> SourceItems );

	UFUNCTION( BlueprintCallable )
	TArray<UItemInfo*> UnlockContainer( TArray<UItemInfo*> SourceItems );

	UFUNCTION( BlueprintCallable )
	TArray<UItemInfo*> ContainItem( TArray<UItemInfo*> SourceItems );
	
};
