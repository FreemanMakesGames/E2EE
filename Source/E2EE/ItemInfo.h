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

	UFUNCTION( BlueprintCallable )
	TSubclassOf<AItem> GetItemClass();

	UFUNCTION( BlueprintCallable )
	TSubclassOf<UItemWidget> GetItemWidgetClass();

	UFUNCTION( BlueprintCallable )
	int GetItemTypeId();

	UFUNCTION( BlueprintCallable )
	TArray<EItemUsage> GetItemUsages();

	virtual bool IsSupportedForNetworking() const override
	{
		return true;
	}

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
	AItem* SpawnItem( const FTransform& SpawnTransform );

	UFUNCTION( BlueprintCallable )
	virtual UItemInfo* Duplicate() PURE_VIRTUAL( , return nullptr; );
	
};
