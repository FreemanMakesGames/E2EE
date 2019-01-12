/* This component finds the first primitive component of the owner.
 * If the primitive is clicked, the actor is destroyed, and an item is picked up.
 */


#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PickupComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class E2EE_API UPickupComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPickupComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void Pickup( UPrimitiveComponent* TouchedComponent, FKey ButtonPressed );

	UPROPERTY( EditAnywhere )
	AActor* ItemReceiver;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};
