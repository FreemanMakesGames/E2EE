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
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic( this, &ABot::OnCapsuleBeginOverlap );
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic( this, &ABot::OnCapsuleEndOverlap );

	ShouldMove = true;
	IsOnTheWay = false;
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

void ABot::Tick( float DeltaSeconds )
{
	if ( TargetWaypoints.Num() > 0 && ShouldMove && !IsOnTheWay )
	{
		AIController->MoveToActor( TargetWaypoints[0] );

		IsOnTheWay = true;
	}
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

void ABot::OnCapsuleBeginOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult )
{
	if ( AWaypoint* Waypoint = Cast<AWaypoint>( OtherActor ) )
	{
		CurrentWaypoint = Waypoint;
	}
}

void ABot::OnCapsuleEndOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex )
{
	if ( Cast<AWaypoint>( OtherActor ) )
	{
		CurrentWaypoint = nullptr;
	}
}

void ABot::OnMoveCompleted( FAIRequestID RequestID, EPathFollowingResult::Type Result )
{
	IsOnTheWay = false;

	if ( Result == EPathFollowingResult::Success )
	{
		// If we've reached a target waypoint.
		// ( There may be better ways of detecting this, such as adding a IsGoingToWaypoint global variable. This project currently doesn't need it. )
		if ( TargetWaypoints.Num() > 0 && CurrentWaypoint == TargetWaypoints[0] )
		{
			TargetWaypoints.RemoveAt( 0 );

			ShouldMove = false; // For inventory activities

			if ( CurrentWaypoint == Waypoint_Alice || CurrentWaypoint == Waypoint_Bob )
			{
				TArray<AItem*> DroppedItems = CurrentWaypoint->GetDroppedItems();

				if ( DroppedItems.Num() > 0 )
				{
					for ( AItem* Item : DroppedItems )
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
				else
				{
					PlayerController->DisplayNotification( NSLOCTEXT( "", "", "No item is dropped in the area for the messenger to send." ) );
				}

			}
			else if ( CurrentWaypoint == Waypoint_Middle )
			{
				ShowInventory();


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
	if ( CurrentWaypoint == Waypoint_Alice )
	{
		TargetWaypoints.Add( Waypoint_Middle );
		TargetWaypoints.Add( Waypoint_Bob );
	}
	else if ( CurrentWaypoint == Waypoint_Bob )
	{
		TargetWaypoints.Add( Waypoint_Middle );
		TargetWaypoints.Add( Waypoint_Alice );
	}
	else if ( CurrentWaypoint == Waypoint_Middle )
	{

	}

	ShouldMove = true;
}

void ABot::Summon()
{
	UDevUtilities::PrintInfo( "Messenger is being summoned." );

	// Don't move if there's no active character.
	ABasicCharacter* ActiveCharacter = PlayerController->GetActiveCharacter();
	if ( ActiveCharacter )
	{
		if ( ActiveCharacter->GetUsername() == "Alice" )
		{
			TargetWaypoints.Add( Waypoint_Alice );
			ShouldMove = true;
		}
		else if ( ActiveCharacter->GetUsername() == "Bob" )
		{
			TargetWaypoints.Add( Waypoint_Bob );
			ShouldMove = true;
		}
		else
		{ 
			UDevUtilities::PrintError( "Messenger: Active character's name is an unexpected string." ); return;
		}
	}
	else
	{
		PlayerController->DisplayNotification( NSLOCTEXT( "", "", "Select Alice/Bob before you summon the messenger." ) );
		return;
	}
}
