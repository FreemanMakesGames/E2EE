// #include "ItemCombiner.h"
// 
// #include "Item.h"
// 
// #include "UObject/ConstructorHelpers.h"
// #include "Templates/Function.h"
// 
// UItemCombiner::UItemCombiner()
// {
// 	/* All classes of combinable Items */
// 
// 	static ConstructorHelpers::FClassFinder<AItem> LockClassFinder( TEXT( "/Game/Items/Blueprints/BP_Lock" ) );
// 	TSubclassOf<AItem> LockClass = LockClassFinder.Class;
// 	
// 	static ConstructorHelpers::FClassFinder<AItem> KeyClassFinder( TEXT( "/Game/Items/Blueprints/BP_Key" ) );
// 	TSubclassOf<AItem> KeyClass = KeyClassFinder.Class;
// 	
// 	static ConstructorHelpers::FClassFinder<AItem> ContainerClassFinder( TEXT( "/Game/Items/Blueprints/BP_Container" ) );
// 	TSubclassOf<AItem> ContainerClass = ContainerClassFinder.Class;
// 	
// 	static ConstructorHelpers::FClassFinder<AItem> MessageClassFinder( TEXT( "/Game/Items/Blueprints/BP_Message" ) );
// 	TSubclassOf<AItem> MessageClass = MessageClassFinder.Class;
// 
// 	/* All possible combination among Item types */
// 
// 	TArray<TSubclassOf<AItem>> LockAndContainer;
// 	LockAndContainer.Add( LockClass );
// 	LockAndContainer.Add( ContainerClass );
// 	FArrayOfItemClasses LockAndContainerArray( LockAndContainer );
// 
// 	TArray<TSubclassOf<AItem>> KeyAndContainer;
// 	KeyAndContainer.Add( KeyClass );
// 	KeyAndContainer.Add( ContainerClass );
// 
// 	TArray<TSubclassOf<AItem>> ContainerAndLock;
// 	ContainerAndLock.Add( ContainerClass );
// 	ContainerAndLock.Add( LockClass );
// 
// 	TArray<TSubclassOf<AItem>> ContainerAndKey;
// 	ContainerAndKey.Add( ContainerClass );
// 	ContainerAndKey.Add( KeyClass );
// 
// 	TArray<TSubclassOf<AItem>> ContainerAndMessage;
// 	ContainerAndMessage.Add( ContainerClass );
// 	ContainerAndMessage.Add( MessageClass );
// 
// 	/* Assign functions. */
// // 
// // 	LockContainerFunction.BindUObject( this, &UItemCombiner::LockContainer );
// // 
// // 	UnlockContainerFunction.BindUObject( this, &UItemCombiner::UnlockContainer );
// 
// 	/* Populate the function map. */
// 
// 	FunctionIndexMap.Add( LockAndContainerArray, 0 );
// }
// 
// void UItemCombiner::CombineItems()
// {
// 
// }
// 
// void UItemCombiner::SetSourceItems( TArray<AItem*> Items )
// {
// 	SourceItems = Items;
// }
// 
// TArray<AItem*> UItemCombiner::GetResultItems()
// {
// 	return ResultItems;
// }
// 
// void UItemCombiner::LockContainer()
// {
// 
// }
// 
// void UItemCombiner::UnlockContainer()
// {
// 
// }
