// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Navigation/PathFollowingComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Bot.generated.h"

class AAIController;
class UBotInventoryMenu;

UENUM( BlueprintType )
enum class EBotMissionStatus : uint8
{
	Idle				UMETA( DisplayName = "Idle" ),

	Summoned			UMETA( DisplayName = "Summoned" ),

	CollectingItems		UMETA( DisplayName = "CollectingItems" ),

	DuplicatingItems	UMETA( DisplayName = "DuplicatingItems" ),

	DeliveringItems		UMETA( DisplayName = "DeliveringItems" )
};

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

	virtual void Tick( float DeltaSeconds ) override;

#pragma region Getters and setters
public:

	UFUNCTION( BlueprintCallable )
	UInventory* GetInventory();

	UFUNCTION( BlueprintCallable )
	AWaypoint* GetCurrentWaypoint();

	UFUNCTION( BlueprintCallable )
	void SetCurrentWaypoint( AWaypoint* TheWaypoint );
#pragma endregion

protected:

	UPROPERTY( EditDefaultsOnly )
	TSubclassOf<UBotInventoryMenu> InventoryMenuClass;

	UPROPERTY( EditInstanceOnly, BlueprintReadOnly )
	AWaypoint* Waypoint_Alice;

	UPROPERTY( EditInstanceOnly, BlueprintReadOnly )
	AWaypoint* Waypoint_Bob;

	UPROPERTY( EditInstanceOnly, BlueprintReadOnly )
	AWaypoint* Waypoint_Middle;

protected:

	UPROPERTY( BlueprintReadOnly )
	UInventory* Inventory;

	UPROPERTY( BlueprintReadOnly )
	UBotInventoryMenu* InventoryMenu;

	UPROPERTY( BlueprintReadOnly )
	AAIController* AIController;

protected:

	UFUNCTION()
	void OnCapsuleClicked( UPrimitiveComponent* TouchedComponent, FKey ButtonPressed ); // Due to a UE bug, this can't be named as HandleOnCapsuleClicked...

	UFUNCTION()
	void HandleOnCapsuleBeginOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult );

	UFUNCTION()
	void HandleOnCapsuleEndOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex );

	UFUNCTION()
	void HandleOnMoveCompleted( FAIRequestID RequestID, EPathFollowingResult::Type Result );

	UFUNCTION()
	void HandleOnInventoryMenuPreDuplicationHighlightFinished();

	UFUNCTION()
	void HandleOnInventoryMenuHidden();

protected:

	UFUNCTION( BlueprintCallable )
	void Summon();

	/** @return Whether Bot actually starts moving based on other conditions */
	UFUNCTION( BlueprintCallable )
	bool StartMove();

	UFUNCTION( BlueprintCallable )
	bool ShouldMove();

protected:

	UPROPERTY( BlueprintReadOnly )
	ABasicPlayerController* PlayerController;

	UPROPERTY( VisibleInstanceOnly )
	TArray<AWaypoint*> TargetWaypoints;

	UPROPERTY( VisibleInstanceOnly )
	AWaypoint* CurrentWaypoint;

	UPROPERTY( BlueprintReadOnly )
	TArray<UItemInfo*> ItemsToDeliver;

	UPROPERTY( VisibleInstanceOnly )
	EBotMissionStatus MissionStatus;

	bool IsOnTheWay;

	/**
	 * Item clicker's pre-duplication animation fires an event at the end,
	 * Which leads to HandleOnInventoryMenuPreDuplicationHighlightFinished,
	 * Which starts duplications.
	 * If the inventory menu's closed before pre-duplication animation's finished,
	 * Event won't fire, so we need another flag here to ensure duplication.
	 */
	//bool PendingDuplication;

};
