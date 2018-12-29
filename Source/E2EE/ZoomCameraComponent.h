/* This component finds the first primitive component of the owner.
 * If the primitive is clicked, the view target is set to this camera.
 */

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "ZoomCameraComponent.generated.h"

struct FKey;

UCLASS( Blueprintable, BlueprintType, ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent ) )
class E2EE_API UZoomCameraComponent : public UCameraComponent
{
	GENERATED_BODY()

public:

	UZoomCameraComponent();

protected:

	//virtual void BeginPlay() override;

	UFUNCTION()
	void ZoomIn( UPrimitiveComponent* TouchedComponent, FKey ButtonPressed );

};
