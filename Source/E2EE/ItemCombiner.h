#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemCombiner.generated.h"

class AItem;
class UItemInfo;

USTRUCT()
struct FArrayOfItemClasses
{
	GENERATED_BODY()

public:

	FArrayOfItemClasses() {}

	FArrayOfItemClasses( TArray<TSubclassOf<UItemInfo>> ItemClasses )
	{
		this->ItemClasses = ItemClasses;
	}

	UPROPERTY()
	TArray<TSubclassOf<UItemInfo>> ItemClasses;

	bool operator==( const FArrayOfItemClasses& Other ) const
	{
		return ItemClasses == Other.ItemClasses;
	}
};

FORCEINLINE uint32 GetTypeHash( const FArrayOfItemClasses& ArrayOfItems )
{
	return FCrc::MemCrc_DEPRECATED( &ArrayOfItems, sizeof( FArrayOfItemClasses ) );
}

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

// Blueprint classes
// protected:
// 	
// 	UPROPERTY( EditDefaultsOnly )
// 	TSubclassOf<AItem> LockClass;
// 	
// 	UPROPERTY( EditDefaultsOnly )
// 	TSubclassOf<AItem> KeyClass;
// 	
// 	UPROPERTY( EditDefaultsOnly )
// 	TSubclassOf<AItem> ContainerClass;
// 	
// 	UPROPERTY( EditDefaultsOnly )
// 	TSubclassOf<AItem> MessageClass;

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
