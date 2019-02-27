// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "Waypoint.generated.h"

class UBoxComponent;

UCLASS()
class E2EE_API AWaypoint : public ATargetPoint
{
	GENERATED_BODY()

public:

	AWaypoint();

	UFUNCTION( BlueprintPure )
	FVector GetDefaultItemDropOffLocation();

	UFUNCTION( BlueprintPure )
	TArray<ACharacter*> GetOccupants();

protected:

	UPROPERTY( VisibleInstanceOnly )
	UBoxComponent* TriggerBox;

	UPROPERTY( VisibleInstanceOnly )
	USceneComponent* DefaultItemDropOff;

	UFUNCTION()
	void HandleOnBoxBeginOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult );

	UFUNCTION()
	void HandleOnBoxEndOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex );

	UPROPERTY( VisibleAnywhere )
	TArray<ACharacter*> Occupants;

};
