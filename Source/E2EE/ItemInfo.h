#pragma once

#include "ItemUsage.h"

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemInfo.generated.h"

class AItem;
class UItemWidget;


/**
 * 
 */
UCLASS( Blueprintable, BlueprintType )
class E2EE_API UItemInfo : public UObject
{
	GENERATED_BODY()

public:

	virtual bool IsSupportedForNetworking() const override
	{
		return true;
	}

public:

	UFUNCTION( BlueprintCallable )
	TSubclassOf<AItem> GetItemClass();

	UFUNCTION( BlueprintCallable )
	TSubclassOf<UItemWidget> GetItemWidgetClass();

	UFUNCTION( BlueprintCallable )
	int GetItemTypeId();

	UFUNCTION( BlueprintCallable )
	TArray<EItemUsage> GetItemUsages();

protected:

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	TSubclassOf<AItem> ItemClass;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	TSubclassOf<UItemWidget> ItemWidgetClass;

	int ItemTypeId;

	UPROPERTY( Replicated )
	TArray<EItemUsage> ItemUsages;

public:

	UFUNCTION( BlueprintCallable )
	virtual UItemInfo* Duplicate() PURE_VIRTUAL( , return nullptr; );

	UFUNCTION( BlueprintCallable )
	virtual FText Describe() PURE_VIRTUAL( , return NSLOCTEXT( "", "", "Invalid description!" ); );

	UFUNCTION( BlueprintCallable )
	virtual bool IsEquivalentTo( UItemInfo* OtherItem ) PURE_VIRTUAL( , return false; );

public:

	UFUNCTION( BlueprintCallable )
	AItem* SpawnItem( const FTransform& SpawnTransform );
	
};
