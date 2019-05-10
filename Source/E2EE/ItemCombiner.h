// #pragma once
// 
// #include "CoreMinimal.h"
// #include "UObject/NoExportTypes.h"
// #include "ItemCombiner.generated.h"
// 
// class AItem;
// 
// DECLARE_DELEGATE( FCombineFunction );
// 
// USTRUCT()
// struct FArrayOfItemClasses
// {
// 	GENERATED_BODY()
// 
// public:
// 
// 	FArrayOfItemClasses( TArray<TSubclassOf<AItem>> Items )
// 	{
// 		this->Items = Items;
// 	}
// 
// 	UPROPERTY()
// 	TArray<TSubclassOf<AItem>> Items;
// 
// 	bool operator==( const FArrayOfItemClasses& Other ) const
// 	{
// 		return Items == Other.Items;
// 	}
// };
// 
// FORCEINLINE uint32 GetTypeHash( const FArrayOfItemClasses& ArrayOfItems )
// {
// 	return FCrc::MemCrc_DEPRECATED( &ArrayOfItems, sizeof( FArrayOfItemClasses ) );
// }
// 
// /**
//  * 
//  */
// UCLASS( BlueprintType )
// class E2EE_API UItemCombiner : public UObject
// {
// 	GENERATED_BODY()
// 
// public:
// 
// 	UItemCombiner();
// 
// public:
// 
// 	UFUNCTION( BlueprintCallable )
// 	void CombineItems();
// 
// // Blueprint classes
// // protected:
// // 	
// // 	UPROPERTY( EditDefaultsOnly )
// // 	TSubclassOf<AItem> LockClass;
// // 	
// // 	UPROPERTY( EditDefaultsOnly )
// // 	TSubclassOf<AItem> KeyClass;
// // 	
// // 	UPROPERTY( EditDefaultsOnly )
// // 	TSubclassOf<AItem> ContainerClass;
// // 	
// // 	UPROPERTY( EditDefaultsOnly )
// // 	TSubclassOf<AItem> MessageClass;
// 
// protected:
// 
// // 	UPROPERTY( VisibleAnywhere )
// // 	TMap<FArrayOfItems, TFunction<void()>> FunctionMap;
// 
// 	UPROPERTY( VisibleAnywhere )
// 	TMap<FArrayOfItemClasses, int> FunctionIndexMap;
// 
// public:
// 
// 	void SetSourceItems( TArray<AItem*> Items );
// 
// 	TArray<AItem*> GetResultItems();
// 
// protected:
// 
// 	UPROPERTY()
// 	TArray<AItem*> SourceItems;
// 
// 	UPROPERTY()
// 	TArray<AItem*> ResultItems;
// 
// // protected:
// // 
// // 	FCombineFunction LockContainerFunction;
// // 
// // 	FCombineFunction UnlockContainerFunction;
// 
// protected:
// 
// 	UFUNCTION( BlueprintCallable )
// 	void LockContainer();
// 
// 	UFUNCTION( BlueprintCallable )
// 	void UnlockContainer();
// 	
// };
