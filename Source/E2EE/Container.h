#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Container.generated.h"

class UContainerItemInfo;
class UContainerItemWidget;

class UStaticMeshComponent;
class UPickupComponent;
class UHighlightComponent;

/**
 *
 */
UCLASS()
class E2EE_API AContainer : public AItem
{
	GENERATED_BODY()

public:

	AContainer( const FObjectInitializer& ObjectInitializer );

public:

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	UPickupComponent* PickupComponent;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	UHighlightComponent* HightlightComponent;

};
