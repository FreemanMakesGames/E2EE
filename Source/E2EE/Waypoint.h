// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "Waypoint.generated.h"

class UBoxComponent;
class AItem;

UCLASS()
class E2EE_API AWaypoint : public ATargetPoint
{
	GENERATED_BODY()

public:

	AWaypoint();

public:

	UFUNCTION( BlueprintPure )
	FVector GetDefaultItemDropOffLocation();

	UFUNCTION( BlueprintPure )
	TArray<ACharacter*> GetOccupants();

	UFUNCTION( BlueprintCallable )
	TArray<AItem*> GetDroppedItems();

protected:

	UPROPERTY( VisibleInstanceOnly )
	UBoxComponent* TriggerBox;

	UPROPERTY( VisibleInstanceOnly )
	USceneComponent* DefaultItemDropOff;

	UPROPERTY( VisibleInstanceOnly )
	TArray<ACharacter*> Occupants;

	UPROPERTY( VisibleInstanceOnly )
	TArray<AItem*> DroppedItems;

protected:

	UFUNCTION()
	void HandleOnBoxBeginOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult );

	UFUNCTION()
	void HandleOnBoxEndOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex );

};
