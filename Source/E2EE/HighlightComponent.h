/* This component finds the first static mesh component of the owner.
 * If the static mesh is moused over, it will be highlighted.
 */

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HighlightComponent.generated.h"

class UUserWidget;

UCLASS( ClassGroup=(Custom), meta=( BlueprintSpawnableComponent ) )
class E2EE_API UHighlightComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHighlightComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void Highlight( UPrimitiveComponent* TouchedComponent );

	UFUNCTION()
	void EndHighlight( UPrimitiveComponent* TouchedComponent );

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
