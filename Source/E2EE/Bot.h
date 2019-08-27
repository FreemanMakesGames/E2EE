// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Navigation/PathFollowingComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Bot.generated.h"

class AAIController;
class UBotInventoryMenu;
class UInventory;

UENUM( BlueprintType )
enum class EBotMissionStatus : uint8
{
	Idle				UMETA( DisplayName = "Idle" ),

	Summoned			UMETA( DisplayName = "Summoned" ),

	CollectingItems		UMETA( DisplayName = "CollectingItems" ),

	DuplicatingItems	UMETA( DisplayName = "DuplicatingItems" ),

	ExaminingItems		UMETA( DisplayName = "ExaminingItems" ),

	ExaminationComplete UMETA( DisplayName = "ExaminationComplete" ),

	OpeningContainer	UMETA( DisplayName = "OpeningContainer" ),

	UnlockingContainer	UMETA( DisplayName = "UnlockingContainer" ),

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

#pragma region Capsule event handlers
	UFUNCTION()
	void OnCapsuleClicked( UPrimitiveComponent* TouchedComponent, FKey ButtonPressed ); // Due to a UE bug, this can't be named as HandleOnCapsuleClicked...

	UFUNCTION()
	void HandleOnCapsuleBeginOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult );

	UFUNCTION()
	void HandleOnCapsuleEndOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex );
#pragma endregion

	UFUNCTION()
	void HandleOnMoveCompleted( FAIRequestID RequestID, EPathFollowingResult::Type Result );

	UFUNCTION()
	void HandleOnInventoryMenuAdditionHighlightFinished();

	UFUNCTION()
	void HandleOnInventoryMenuPreDuplicationHighlightFinished();

	UFUNCTION()
	void HandleOnInventoryMenuContainerOpenHighlightFinished( UContainerItemInfo* Container );

	UFUNCTION()
	void HandleOnInventoryMenuContainerUnlockHighlightFinished();

	UFUNCTION()
	void HandleOnInventoryMenuProceed();

protected:

	UFUNCTION( BlueprintCallable )
	void Summon();

	/** @return Whether Bot actually starts moving based on other conditions */
	UFUNCTION( BlueprintCallable )
	bool StartMove();

	UFUNCTION( BlueprintCallable )
	bool ShouldMove();

	void ExamineItems();

protected:

	UPROPERTY( BlueprintReadOnly )
	ABasicPlayerController* PlayerController;

	UPROPERTY( VisibleInstanceOnly )
	TArray<AWaypoint*> TargetWaypoints;

	UPROPERTY( VisibleInstanceOnly )
	AWaypoint* CurrentWaypoint;

	UPROPERTY( BlueprintReadOnly )
	TArray<UItemInfo*> ItemsToDeliver;

	TPair<UKeyItemInfo*, UContainerItemInfo*> KeyAndContainerToUnlockAfterHighlight;

	UPROPERTY( VisibleInstanceOnly )
	EBotMissionStatus MissionStatus;

	bool IsOnTheWay;

};
