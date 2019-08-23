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

public:

	UFUNCTION( BlueprintCallable )
	void ShowInventory();

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
	void OnCapsuleClicked( UPrimitiveComponent* TouchedComponent, FKey ButtonPressed );

	UFUNCTION()
	void OnCapsuleBeginOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult );

	UFUNCTION()
	void OnCapsuleEndOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex );

	UFUNCTION()
	void OnMoveCompleted( FAIRequestID RequestID, EPathFollowingResult::Type Result );

	UFUNCTION()
	void OnInventoryMenuHidden();

protected:

	UFUNCTION( BlueprintCallable )
	void Summon();

	UFUNCTION( BlueprintCallable )
	bool ShouldMove();

protected:

	ABasicPlayerController* PlayerController;

	UPROPERTY( VisibleInstanceOnly )
	TArray<AWaypoint*> TargetWaypoints;

	UPROPERTY( VisibleInstanceOnly )
	AWaypoint* CurrentWaypoint;

	TArray<UItemInfo*> ItemToDeliver;

	UPROPERTY( VisibleInstanceOnly )
	EBotMissionStatus MissionStatus;

	bool IsOnTheWay;

};
