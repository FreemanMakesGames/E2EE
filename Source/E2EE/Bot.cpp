// Fill out your copyright notice in the Description page of Project Settings.

#include "Bot.h"

#include "BasicPlayerController.h"
#include "BasicCharacter.h"
#include "Waypoint.h"
#include "Item.h"
#include "LockItemInfo.h"
#include "KeyItemInfo.h"
#include "ContainerItemInfo.h"
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
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic( this, &ABot::HandleOnCapsuleBeginOverlap );
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic( this, &ABot::HandleOnCapsuleEndOverlap );

	MissionStatus = EBotMissionStatus::Idle;
	IsOnTheWay = false;
}

void ABot::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<ABasicPlayerController>( GetWorld()->GetFirstPlayerController() );

	AIController = GetController<AAIController>();
	AIController->ReceiveMoveCompleted.AddDynamic( this, &ABot::HandleOnMoveCompleted );

	// Create InventoryMenu.
	if ( InventoryMenuClass )
	{
		InventoryMenu = CreateWidget<UBotInventoryMenu>( GetWorld()->GetFirstPlayerController(), InventoryMenuClass );
		InventoryMenu->SetupInventory( Inventory );
		InventoryMenu->OnHidden.AddDynamic( this, &ABot::HandleOnInventoryMenuHidden );
		InventoryMenu->OnPreDuplicationHighlightCompleted.AddDynamic( this, &ABot::HandleOnInventoryMenuPreDuplicationHighlightFinished );
	}
	else { UDevUtilities::PrintError( "ABot's InventoryMenuClass isn't set!" ); return; }
}

void ABot::SetupPlayerInputComponent( UInputComponent* PlayerInputComponent )
{
	Super::SetupPlayerInputComponent( PlayerInputComponent );
}

void ABot::Tick( float DeltaSeconds )
{

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

void ABot::OnCapsuleClicked( UPrimitiveComponent* TouchedComponent, FKey ButtonPressed )
{
	Summon();
}

void ABot::HandleOnCapsuleBeginOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult )
{
	if ( AWaypoint* Waypoint = Cast<AWaypoint>( OtherActor ) )
	{
		CurrentWaypoint = Waypoint;
	}
}

void ABot::HandleOnCapsuleEndOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex )
{
	if ( Cast<AWaypoint>( OtherActor ) )
	{
		CurrentWaypoint = nullptr;
	}
}

void ABot::HandleOnMoveCompleted( FAIRequestID RequestID, EPathFollowingResult::Type Result )
{
	IsOnTheWay = false;

	if ( Result == EPathFollowingResult::Success )
	{
		// If we've reached a target waypoint.
		if ( TargetWaypoints.Num() > 0 && CurrentWaypoint == TargetWaypoints[0] )
		{
			TargetWaypoints.RemoveAt( 0 );

			if ( CurrentWaypoint == Waypoint_Alice || CurrentWaypoint == Waypoint_Bob )
			{
				TArray<AItem*> DroppedItems = CurrentWaypoint->GetDroppedItems();

				if ( MissionStatus == EBotMissionStatus::Summoned )
				{
					// If there are dropped items, collect and immediately start delivery.
					if ( DroppedItems.Num() > 0 )
					{
						MissionStatus = EBotMissionStatus::CollectingItems;

						for ( AItem* Item : DroppedItems )
						{
							if ( UItemInfo* ItemInfo = Item->GetItemInfo() )
							{
								Inventory->AddItem( ItemInfo );

								ItemsToDeliver.Add( ItemInfo );

								Item->Destroy();
							}
							else { ensureAlways( false ); return; }
						}

						InventoryMenu->ShowInventory();

						PlayerController->DisplayNotification( NSLOCTEXT( "", "", "The messenger bot has collected the items." ) );
					}
					// If no dropped items
					else
					{
						PlayerController->DisplayNotification( NSLOCTEXT( "", "", "No item is dropped in the area for the messenger to send." ) );

						MissionStatus = EBotMissionStatus::Idle;
					}
				}
				else if ( MissionStatus == EBotMissionStatus::DeliveringItems )
				{
					for ( UItemInfo* Item : ItemsToDeliver )
					{
						Inventory->DropItem( Item );
					}
					ItemsToDeliver.Empty();

					MissionStatus = EBotMissionStatus::Idle;
				}
			}
			else if ( CurrentWaypoint == Waypoint_Middle )
			{
				InventoryMenu->PreDuplicationHighlight( ItemsToDeliver );

				InventoryMenu->ShowInventory();

				MissionStatus = EBotMissionStatus::DuplicatingItems;
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

/**
 * Currently, this is only subscribed when pre-duplication highlight is finished.
 * Alternatively, this can be subscribed in constructor, and then utilizes MissionStatus.
 */
void ABot::HandleOnInventoryMenuAdditionHighlightFinished()
{
	ExamineItems();

	InventoryMenu->OnAdditionHighlightCompleted.RemoveDynamic( this, &ABot::HandleOnInventoryMenuAdditionHighlightFinished );
}

void ABot::HandleOnInventoryMenuPreDuplicationHighlightFinished()
{
	for ( UItemInfo* Item : ItemsToDeliver )
	{
		Inventory->AddItem( Item->Duplicate() );
	}

	InventoryMenu->OnAdditionHighlightCompleted.AddDynamic( this, &ABot::HandleOnInventoryMenuAdditionHighlightFinished );

	MissionStatus = EBotMissionStatus::DeliveringItems;
}

void ABot::HandleOnInventoryMenuHidden()
{
	if ( CurrentWaypoint && ItemsToDeliver.Num() > 0 )
	{
		if ( CurrentWaypoint == Waypoint_Alice )
		{
			TargetWaypoints.Add( Waypoint_Middle );
			TargetWaypoints.Add( Waypoint_Bob );

			MissionStatus = EBotMissionStatus::DeliveringItems;
		}
		else if ( CurrentWaypoint == Waypoint_Bob )
		{
			TargetWaypoints.Add( Waypoint_Middle );
			TargetWaypoints.Add( Waypoint_Alice );

			MissionStatus = EBotMissionStatus::DeliveringItems;
		}
		else if ( CurrentWaypoint == Waypoint_Middle )
		{
			// If duplication isn't done before inventory menu is closed,
			// It won't happen because HandleOnInventoryMenuPreDuplicationHighlightFinished won't fire.
			// So we need to manually duplicate here.
			if ( MissionStatus == EBotMissionStatus::DuplicatingItems )
			{
				for ( UItemInfo* Item : ItemsToDeliver )
				{
					Inventory->AddItem( Item->Duplicate() );
				}

				MissionStatus = EBotMissionStatus::DeliveringItems;
			}
		}

		StartMove();
	}
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
		}
		else if ( ActiveCharacter->GetUsername() == "Bob" )
		{
			TargetWaypoints.Add( Waypoint_Bob );
		}
		else
		{ 
			UDevUtilities::PrintError( "Messenger: Active character's name is an unexpected string." ); return;
		}

		MissionStatus = EBotMissionStatus::Summoned;

		StartMove();
	}
	else
	{
		PlayerController->DisplayNotification( NSLOCTEXT( "", "", "Select Alice/Bob before you summon the messenger." ) );
		return;
	}
}

bool ABot::StartMove()
{
	if ( TargetWaypoints.Num() > 0 && ShouldMove() && !IsOnTheWay )
	{
		// This order is so very important!!!
		// If Bot is already at the destination, MoveToActor calls OnMoveCompleted directly.
		IsOnTheWay = true;
		AIController->MoveToActor( TargetWaypoints[0] );

		return true;
	}
	else
	{
		return false;
	}
}

bool ABot::ShouldMove()
{
	return MissionStatus == EBotMissionStatus::Summoned || MissionStatus == EBotMissionStatus::DeliveringItems;
}

void ABot::ExamineItems()
{
	UDevUtilities::PrintInfo( "Examination starts." );

	TArray<UItemInfo*> ItemsToExamine;
	for ( UItemInfo* Item : Inventory->GetItems() )
	{
		// Don't touch the delivery.
		if ( ItemsToDeliver.Contains( Item ) ) { continue; }

		ItemsToExamine.Add( Item );
	}

	for ( UItemInfo* ItemToExamine : ItemsToExamine )
	{
		if ( UContainerItemInfo* Container = Cast<UContainerItemInfo>( ItemToExamine ) )
		{
			if ( !Container->IsLocked() )
			{


				PlayerController->DisplayNotification( NSLOCTEXT( "", "", "Messenger opens a container." ) );
			}
			else
			{
				for ( UItemInfo* SecondaryItem : ItemsToExamine )
				{
					if ( UKeyItemInfo* KeyItem = Cast<UKeyItemInfo>( SecondaryItem ) )
					{
						if ( KeyItem->GetKeyId() == Container->GetLockId() )
						{


							PlayerController->DisplayNotification( NSLOCTEXT( "", "", "Messenger unlocks a container." ) );
						}
					}
				}
			}
		}
	}
}
