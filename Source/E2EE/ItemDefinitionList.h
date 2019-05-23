#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "ItemDefinitionList.generated.h"

class AItem;
class AItemWidget;

/**
 * 
 */
UCLASS( Blueprintable, BlueprintType  )
class E2EE_API AItemDefinitionList : public AInfo
{
	GENERATED_BODY()

public:

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	TMap<int, TSubclassOf<AItem>> TypeIdToItemClass;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	TMap<int, TSubclassOf<UItemWidget>> TypeIdToItemWidgetClass;
	
};
