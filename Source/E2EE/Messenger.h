// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Messenger.generated.h"

class AAIController;

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

	USkeletalMeshComponent* MySkeletalMeshComponent;
	UCapsuleComponent* MyCapsuleComponent;

	UPROPERTY( BlueprintReadOnly )
	AAIController* MyAIController;

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
