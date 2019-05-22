#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemInfo.generated.h"

/**
 * 
 */
UCLASS()
class E2EE_API UItemInfo : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION( BlueprintCallable )
	int GetItemId();

	UFUNCTION( BlueprintCallable )
	void SetItemId( int InItemId );

protected:

	/** Map this to 3D models, and 2D item widgets, in the definition list. */
	int ItemTypeId;

public:

	UFUNCTION( BlueprintCallable )
	virtual UItemInfo* Duplicate() PURE_VIRTUAL( , return nullptr; );
	
};
