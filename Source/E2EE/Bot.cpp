// Fill out your copyright notice in the Description page of Project Settings.

#include "Bot.h"

#include "BasicPlayerController.h"
#include "BasicCharacter.h"
#include "Waypoint.h"
#include "Item.h"
#include "BotInventoryMenu.h"
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

	PlayerController = Cast<ABasicPlayerController>( GetWorld()->GetFirstPlayerController() );

	AIController = GetController<AAIController>();
	AIController->ReceiveMoveCompleted.AddDynamic( this, &ABot::OnMoveCompleted );

	// Create InventoryMenu.
	if ( InventoryMenuClass )
	{
		InventoryMenu = CreateWidget<UBotInventoryMenu>( GetWorld()->GetFirstPlayerController(), InventoryMenuClass );
		InventoryMenu->SetupInventory( Inventory );
		InventoryMenu->OnHidden.AddDynamic( this, &ABot::OnInventoryMenuHidden );
	}
	else { UDevUtilities::PrintError( "ABot's InventoryMenuClass isn't set!" ); return; }
}

void ABot::SetupPlayerInputComponent( UInputComponent* PlayerInputComponent )
{
	Super::SetupPlayerInputComponent( PlayerInputComponent );
}

#pragma region Getters and setters
UInventory* ABot::GetInventory()
{
	return Inventory;
}

AWaypoint* ABot::GetCurrentWaypoint()
{
	return CurrentWaypoint;
}

void ABot::SetCurrentWaypoint( AWaypoint* TheWaypoint )
{
	CurrentWaypoint = TheWaypoint;
}
#pragma endregion

void ABot::ShowInventory()
{
	InventoryMenu->ShowInventory();
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
		// If we've reached a target waypoint.
		// ( There may be better ways of detecting this, such as adding a IsGoingToWaypoint global variable. This project currently doesn't need it. )
		if ( CurrentWaypoint == TargetWaypoint )
		{
			if ( CurrentWaypoint == Waypoint_Alice || CurrentWaypoint == Waypoint_Bob )
			{
				for ( AItem* Item : CurrentWaypoint->GetDroppedItems() )
				{
					if ( UItemInfo* ItemInfo = Item->GetItemInfo() )
					{
						Inventory->AddItem( ItemInfo );

						Item->Destroy();
					}
					else { ensureAlways( false ); return; }

					ShowInventory();

					PlayerController->DisplayNotification( NSLOCTEXT( "", "", "The messenger bot has collected the items." ) );
				}
			}
			else if ( CurrentWaypoint == Waypoint_Middle )
			{
				// TODO: Duplicate items.
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

void ABot::OnInventoryMenuHidden()
{
	UDevUtilities::PrintInfo( "Bot's inventory menu is hidden." );

	// TODO: Proceed to next step.
}

void ABot::Summon()
{
	UDevUtilities::PrintInfo( "Messenger is being summoned." );

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
