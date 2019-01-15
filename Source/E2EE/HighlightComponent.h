/* This component finds the first primitive component of the owner.
 * If the primitive component is moused over, it will be highlighted.
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

	UHighlightComponent();

protected:

	UFUNCTION()
	void Highlight( UPrimitiveComponent* TouchedComponent );

	UFUNCTION()
	void EndHighlight( UPrimitiveComponent* TouchedComponent );

public:	

};
