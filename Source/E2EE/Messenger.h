// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Messenger.generated.h"

class ATargetPoint;

UCLASS()
class E2EE_API AMessenger : public ACharacter
{
	GENERATED_BODY()

public:

	AMessenger();

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	void HandleOnClicked( UPrimitiveComponent* TouchedComponent, FKey ButtonPressed );

	UFUNCTION()
	void HandleOnCapsuleBeginOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult );

	UFUNCTION()
	void HandleOnCapsuleEndOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex );

	USkeletalMeshComponent* MySkeletalMeshComponent;
	UCapsuleComponent* MyCapsuleComponent;

	UPROPERTY( EditInstanceOnly )
	ATargetPoint* WayPoint_Alice;

	UPROPERTY( EditInstanceOnly )
	ATargetPoint* WayPoint_Bob;

	UPROPERTY( VisibleInstanceOnly )
	ATargetPoint* CurrentWayPoint;

public:	

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	AActor* GetCurrentWayPoint();

};
