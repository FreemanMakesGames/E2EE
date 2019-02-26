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

	UFUNCTION( BlueprintCallable )
	TArray<ACharacter*> GetOccupants();

protected:

	UPROPERTY( VisibleAnywhere )
	UBoxComponent* TriggerBox;

	UFUNCTION()
	void HandleOnBoxBeginOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult );

	UFUNCTION()
	void HandleOnBoxEndOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex );

	UPROPERTY( VisibleAnywhere )
	TArray<ACharacter*> Occupants;

};
