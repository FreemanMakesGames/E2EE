// Fill out your copyright notice in the Description page of Project Settings.

#include "Bot.h"

#include "Item.h"
#include "BasicPlayerController.h"
#include "BasicCharacter.h"
#include "Waypoint.h"
#include "DevUtilities.h"

#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "Runtime/Engine/Classes/AI/NavigationSystemBase.h"
#include "Runtime/AIModule/Classes/AIController.h"

ABot::ABot()
{
	PrimaryActorTick.bCanEverTick = true;

	Inventory = CreateDefaultSubobject<UInventory>( TEXT( "Inventory" ) );

	GetCapsuleComponent()->OnClicked.AddDynamic( this, &ABot::OnCapsuleClicked );
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic( this, &ABot::OnWaypointArrival );
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic( this, &ABot::OnWaypointExit );
}

void ABot::BeginPlay()
{
	Super::BeginPlay();

	AIController = GetController<AAIController>();
	AIController->ReceiveMoveCompleted.AddDynamic( this, &ABot::OnMoveCompleted );
}

void ABot::SetupPlayerInputComponent( UInputComponent* PlayerInputComponent )
{
	Super::SetupPlayerInputComponent( PlayerInputComponent );
}

AWaypoint* ABot::GetCurrentWaypoint()
{
	return CurrentWaypoint;
}

void ABot::SetCurrentWaypoint( AWaypoint* TheWaypoint )
{
	CurrentWaypoint = TheWaypoint;
}

void ABot::OnCapsuleClicked( UPrimitiveComponent* TouchedComponent, FKey ButtonPressed )
{
	Summon();
}

void ABot::OnWaypointArrival( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult )
{
	if ( AWaypoint* Waypoint = Cast<AWaypoint>( OtherActor ) )
	{
		CurrentWaypoint = Waypoint;
	}
}

void ABot::OnWaypointExit( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex )
{
	if ( Cast<AWaypoint>( OtherActor ) )
	{
		CurrentWaypoint = nullptr;
	}
}

void ABot::OnMoveCompleted( FAIRequestID RequestID, EPathFollowingResult::Type Result )
{
	if ( Result == EPathFollowingResult::Success )
	{
		if ( TargetWaypoint == CurrentWaypoint )
		{
			for ( AItem* Item : TargetWaypoint->GetDroppedItems() )
			{
				if ( UItemInfo* ItemInfo = Item->GetItemInfo() )
				{
					Inventory->AddItem( ItemInfo );

					Item->Destroy();
				}
				else
				{
					ensureAlways( false );
					return;
				}
			}
		}
		else
		{
			UDevUtilities::PrintError( "Somehow Bot reaches the destination, but isn't in the target waypoint." );
		}
	}
	else
	{
		UDevUtilities::PrintError( "Somehow Bot fails to reach the destination." );
	}
}

void ABot::Summon()
{
	UDevUtilities::PrintInfo( "Messenger is being summoned." );

	ABasicPlayerController* PlayerController = Cast<ABasicPlayerController>( GetWorld()->GetFirstPlayerController() );

	// Get target waypoint.
	// Don't move if there's no active character.
	ABasicCharacter* ActiveCharacter = PlayerController->GetActiveCharacter();
	if ( ActiveCharacter )
	{
		if ( ActiveCharacter->GetUsername() == "Alice" ) { TargetWaypoint = Waypoint_Alice; }
		else if ( ActiveCharacter->GetUsername() == "Bob" ) { TargetWaypoint = Waypoint_Bob; }
		else { UDevUtilities::PrintError( "Messenger: Active character's name is an unexpected string." ); return; }
	}
	else
	{
		PlayerController->DisplayNotification( NSLOCTEXT( "", "", "Select Alice/Bob before you summon the messenger." ) );

		return;
	}

	// Only move if there are dropped items in TargetWaypoint.
	if ( TargetWaypoint->GetDroppedItems().Num() > 0 )
	{
		AIController->MoveToActor( TargetWaypoint );
	}
	else
	{
		PlayerController->DisplayNotification( NSLOCTEXT( "", "", "No item is dropped in the area for the messenger to send." ) );
	}
}
