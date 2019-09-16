// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Team.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BasicCharacter.generated.h"

class UInventory;
class UPlayerInventoryMenu;
class AItem;
class ABot;
class UHighlightComponent;
class UDropItemComponent;
class AWaypoint;
class ABasicPlayerController;
class UPlayableCharacterMenu;

class UUserWidget;
class UWidgetComponent;
class ACameraActor;

UCLASS(config=Game)
class ABasicCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	ABasicCharacter();

#pragma region Unreal Engine default input setup
public:

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

#pragma endregion

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	virtual void BeginPlay() override;

#pragma region Getters and setters
public:

	UFUNCTION( BlueprintCallable )
	UInventory* GetInventory();

	UFUNCTION( BlueprintCallable )
	ETeam GetTeam();

	UFUNCTION( BlueprintCallable )
	AWaypoint* GetAssignedWaypoint();

	UFUNCTION( BlueprintCallable )
	void SetAssignedWaypoint( AWaypoint* InWaypoint );

	UFUNCTION( BlueprintCallable )
	FText GetUsername();
#pragma endregion

protected:

	UPROPERTY( EditDefaultsOnly )
	TSubclassOf<UPlayerInventoryMenu> InventoryMenuClass;

	UPROPERTY( EditDefaultsOnly )
	TSubclassOf<UPlayableCharacterMenu> PlayableCharacterMenuClass;

	UPROPERTY( EditInstanceOnly )
	AWaypoint* AssignedWaypoint;

	UPROPERTY( EditInstanceOnly )
	ABot* Bot;

	UPROPERTY( EditInstanceOnly )
	FText Username;

	UPROPERTY( EditDefaultsOnly )
	ETeam Team;

protected:

	UPROPERTY( BlueprintReadOnly )
	UInventory* Inventory;

	UPROPERTY( BlueprintReadOnly )
	UPlayerInventoryMenu* InventoryMenu;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	UWidgetComponent* PlayableCharacterMenuComponent;

	UPROPERTY( BlueprintReadOnly )
	UPlayableCharacterMenu* PlayableCharacterMenu;

	UPROPERTY( EditInstanceOnly, BlueprintReadOnly )
	ACameraActor* Camera_Focus;

	UPROPERTY( EditInstanceOnly, BlueprintReadOnly )
	ACameraActor* Camera_Overview;

public:

	// TODO: Can these be friend functions?
	void ShowInventory();
	void PickUpItems();
	void SendItems();
	void Unfocus();

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable )
	void ReadItem( UItemInfo* ItemToRead );

	UFUNCTION( BlueprintImplementableEvent )
	void ToggleWidget( bool On );

protected:

	UFUNCTION()
	void HandleOnCapsuleClicked( UPrimitiveComponent* TouchedComponent, FKey ButtonPressed );

protected:

	ABasicPlayerController* PlayerController;

};

