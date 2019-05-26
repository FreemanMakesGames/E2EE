#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemCombiner.generated.h"

class AItem;
class UItemInfo;

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

protected:

	TMap<FArrayOfItemTypeId, FCombineFunction> FunctionMap;

public:

	UFUNCTION( BlueprintCallable )
	TArray<UItemInfo*> CombineItems( TArray<UItemInfo*> SourceItems );

protected:

	UFUNCTION( BlueprintCallable )
	TArray<UItemInfo*> LockContainer( TArray<UItemInfo*> SourceItems );

	UFUNCTION( BlueprintCallable )
	TArray<UItemInfo*> UnlockContainer( TArray<UItemInfo*> SourceItems );
	
};
