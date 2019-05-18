// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Team.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BasicCharacter.generated.h"

class AItem;
class UInventory;
class UUserWidget;
class UHighlightComponent;
class UDropItemComponent;
class ACameraActor;

class AWaypoint;

UCLASS(config=Game)
class ABasicCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	ABasicCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	virtual void BeginPlay() override;

public:

	UFUNCTION( BlueprintCallable )
	UInventory* GetInventory();

	UFUNCTION( BlueprintCallable )
	ETeam GetTeam();

	UFUNCTION( BlueprintCallable )
	AWaypoint* GetCurrentWaypoint();

	UFUNCTION( BlueprintCallable )
	void SetCurrentWaypoint( AWaypoint* TheWaypoint );

	UFUNCTION( BlueprintCallable )
	FString GetUsername();

protected:

	UPROPERTY( BlueprintReadWrite )
	UInventory* Inventory;

	UPROPERTY( EditDefaultsOnly )
	ETeam Team;

	UPROPERTY( VisibleInstanceOnly )
	AWaypoint* CurrentWaypoint;

	UPROPERTY( EditInstanceOnly )
	FString Username;

public:

	UFUNCTION( Server, Reliable, WithValidation, BlueprintCallable )
	void ServerDisablePickedUpActor( AActor* PickedUpActor );

	UFUNCTION( NetMulticast, Reliable, BlueprintCallable )
	void MulticastDisablePickedUpActor( AActor* PickedUpActor );

	UFUNCTION( BlueprintImplementableEvent )
	void ToggleWidget( bool On );

	UPROPERTY( EditInstanceOnly, BlueprintReadOnly )
	ACameraActor* Camera;

protected:

	UFUNCTION()
	void HandleOnCapsuleClicked( UPrimitiveComponent* TouchedComponent, FKey ButtonPressed );



};

