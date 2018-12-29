// Fill out your copyright notice in the Description page of Project Settings.

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
