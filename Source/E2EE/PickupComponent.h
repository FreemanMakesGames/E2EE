/* This component finds the first primitive component of the owner.
 * If the primitive is clicked, the actor is destroyed, and an item is picked up.
 */

#pragma once

#include "Item.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PickupComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class E2EE_API UPickupComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UPickupComponent();

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	void Pickup( UPrimitiveComponent* TouchedComponent, FKey ButtonPressed );

	UPROPERTY( EditAnywhere )
	FItem MyItem;

	UPROPERTY( EditAnywhere )
	AActor* ItemReceiver;

	AActor* MyOwner;

public:	

};
