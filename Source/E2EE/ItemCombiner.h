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

	FArrayOfItemClasses( TArray<TSubclassOf<AItem>> ItemClasses )
	{
		this->ItemClasses = ItemClasses;
	}

	UPROPERTY()
	TArray<TSubclassOf<AItem>> ItemClasses;

	bool operator==( const FArrayOfItemClasses& Other ) const
	{
		return ItemClasses == Other.ItemClasses;
	}
};

FORCEINLINE uint32 GetTypeHash( const FArrayOfItemClasses& ArrayOfItems )
{
	return FCrc::MemCrc_DEPRECATED( &ArrayOfItems, sizeof( FArrayOfItemClasses ) );
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

	TMap<FArrayOfItemClasses, FCombineFunction> FunctionMap;
	//FCombineFunction CombineFunctions[30];

public:

	UFUNCTION( BlueprintCallable )
	TArray<UItemInfo*> CombineItems( TArray<UItemInfo*> SourceItems );

protected:

	UFUNCTION( BlueprintCallable )
	TArray<UItemInfo*> LockContainer( TArray<UItemInfo*> SourceItems );

	UFUNCTION( BlueprintCallable )
	TArray<UItemInfo*> UnlockContainer( TArray<UItemInfo*> SourceItems );
	
};
