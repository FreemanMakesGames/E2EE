// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Navigation/PathFollowingComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Bot.generated.h"

class AAIController;
class UBotInventoryMenu;

UCLASS( Blueprintable )
class E2EE_API ABot : public ACharacter
{
	GENERATED_BODY()

public:

	ABot();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

#pragma region Getters and setters
public:

	UFUNCTION( BlueprintCallable )
	UInventory* GetInventory();

	UFUNCTION( BlueprintCallable )
	AWaypoint* GetCurrentWaypoint();

	UFUNCTION( BlueprintCallable )
	void SetCurrentWaypoint( AWaypoint* TheWaypoint );
#pragma endregion

public:

	UFUNCTION( BlueprintCallable )
	void ShowInventory();

protected:

	UPROPERTY( EditDefaultsOnly )
	TSubclassOf<UBotInventoryMenu> InventoryMenuClass;

protected:

	UPROPERTY( BlueprintReadOnly )
	UInventory* Inventory;

	UPROPERTY( BlueprintReadOnly )
	UBotInventoryMenu* InventoryMenu;

	UPROPERTY( BlueprintReadOnly )
	AAIController* AIController;

protected:

	UFUNCTION()
	void OnCapsuleClicked( UPrimitiveComponent* TouchedComponent, FKey ButtonPressed );

	UFUNCTION()
	void OnWaypointArrival( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult );

	UFUNCTION()
	void OnWaypointExit( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex );

	UFUNCTION()
	void OnMoveCompleted( FAIRequestID RequestID, EPathFollowingResult::Type Result );

protected:

	UFUNCTION( BlueprintCallable )
	void Summon();

protected:

	ABasicPlayerController* PlayerController;

	UPROPERTY( EditInstanceOnly, BlueprintReadOnly )
	AWaypoint* Waypoint_Alice;

	UPROPERTY( EditInstanceOnly, BlueprintReadOnly )
	AWaypoint* Waypoint_Bob;

	UPROPERTY( VisibleInstanceOnly )
	AWaypoint* TargetWaypoint;

	UPROPERTY( VisibleInstanceOnly )
	AWaypoint* CurrentWaypoint;

};
