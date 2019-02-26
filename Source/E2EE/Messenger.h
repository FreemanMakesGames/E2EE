// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Messenger.generated.h"

class AWaypoint;

UCLASS()
class E2EE_API AMessenger : public ACharacter
{
	GENERATED_BODY()

public:

	AMessenger();

protected:

	virtual void BeginPlay() override;

	UFUNCTION( BlueprintCallable )
	void Summon();

	UFUNCTION( BlueprintCallable )
	void MoveToWaypoint( AWaypoint* TargetWaypoint );

	USkeletalMeshComponent* MySkeletalMeshComponent;
	UCapsuleComponent* MyCapsuleComponent;

	UPROPERTY( EditInstanceOnly, BlueprintReadOnly )
	AWaypoint* Waypoint_Alice;

	UPROPERTY( EditInstanceOnly, BlueprintReadOnly )
	AWaypoint* Waypoint_Bob;

	UPROPERTY( VisibleInstanceOnly )
	AWaypoint* CurrentWaypoint;

public:	

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION( BlueprintCallable )
	AWaypoint* GetCurrentWaypoint();

	UFUNCTION( BlueprintCallable )
	void SetCurrentWaypoint( AWaypoint* TheWaypoint );

};
