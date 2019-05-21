#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PickupComponent.generated.h"

class AItem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class E2EE_API UPickupComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UPickupComponent();

protected:

	virtual void BeginPlay() override;

protected:

	UPROPERTY( BlueprintReadWrite )
	AItem* OwnerItem;

	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	float PickupRange;

protected:

	UFUNCTION()
	void PickUp( UPrimitiveComponent* TouchedComponent, FKey ButtonPressed );
		
};
