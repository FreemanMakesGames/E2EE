#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemWidget.generated.h"

class UItemInfo;

/**
 * 
 */
UCLASS()
class E2EE_API UItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	/** Initialize ItemWidget with ItemInfo here. */
	UFUNCTION( BlueprintCallable )
	virtual void SetItemInfo( UItemInfo* InItemInfo ) PURE_VIRTUAL( , );

};
