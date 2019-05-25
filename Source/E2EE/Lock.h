#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Lock.generated.h"

class ULockItemInfo;
class ULockItemWidget;

class UStaticMeshComponent;
class UPickupComponent;
class UHighlightComponent;

/**
 * 
 */
UCLASS()
class E2EE_API ALock : public AItem
{
	GENERATED_BODY()

public:

	ALock( const FObjectInitializer& ObjectInitializer );

public:

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	UPickupComponent* PickupComponent;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	UHighlightComponent* HightlightComponent;

};