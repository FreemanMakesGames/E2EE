// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Messenger.generated.h"

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

	USkeletalMeshComponent* MySkeletalMeshComponent;

	UPROPERTY( EditInstanceOnly )
	AActor* WayPoint_Alice;

	UPROPERTY( EditInstanceOnly )
	AActor* WayPoint_Bob;

public:	

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
