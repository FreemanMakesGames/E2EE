// Fill out your copyright notice in the Description page of Project Settings.

#include "Bot.h"

#include "BasicPlayerController.h"
#include "BasicCharacter.h"
#include "Waypoint.h"
#include "Item.h"
#include "Inventory.h"
#include "LockItemInfo.h"
#include "KeyItemInfo.h"
#include "ContainerItemInfo.h"
#include "MessageItemInfo.h"
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
		InventoryMenu->OnProceed.AddDynamic( this, &ABot::HandleOnInventoryMenuProceed );
	}
	else { UDevUtilities::PrintError( "ABot's InventoryMenuClass isn't set!" ); return; }
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

#pragma region Capsule event handlers
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
#pragma endregion

void ABot::HandleOnMoveCompleted( FAIRequestID RequestID, EPathFollowingResult::Type Result )
{
	IsOnTheWay = false;

	if ( Result == EPathFollowingResult::Success )
	{
		// If Bot reached a target waypoint
		if ( TargetWaypoints.Num() > 0 && CurrentWaypoint == TargetWaypoints[0] )
		{
			TargetWaypoints.RemoveAt( 0 );

			// If it's end user's waypoint
			if ( CurrentWaypoint == Waypoint_Alice || CurrentWaypoint == Waypoint_Bob )
			{
				TArray<AItem*> DroppedItems = CurrentWaypoint->GetDroppedItems();

				// If on the way to collect items
				if ( MissionStatus == EBotMissionStatus::Summoned )
				{
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
					else
					{
						PlayerController->DisplayNotification( NSLOCTEXT( "", "", "No item is dropped in the area for the messenger to send." ) );

						MissionStatus = EBotMissionStatus::Idle;
					}
				}
				// If on the way to deliver items, drop off the delivery.
				else if ( MissionStatus == EBotMissionStatus::DeliveringItems )
				{
					// TODO: Extract method.
					for ( UItemInfo* Item : ItemsToDeliver )
					{
						Inventory->DropItem( Item );
					}
					ItemsToDeliver.Empty();
					ItemsToDuplicate.Empty();

					MissionStatus = EBotMissionStatus::Idle;
				}
			}
			// If it's Bot's waypoint, start duplicating / examining items.
			else if ( CurrentWaypoint == Waypoint_Middle )
			{
				InventoryMenu->ShowInventory();

				for ( UItemInfo* Item : ItemsToDeliver )
				{
					if ( ShouldDuplicate( Item ) )
					{
						ItemsToDuplicate.Add( Item );
					}
				}

				if ( ItemsToDuplicate.Num() > 0 )
				{
					InventoryMenu->OnPreDuplicationHighlightCompleted.AddDynamic( this, &ABot::HandleOnInventoryMenuPreDuplicationHighlightFinished );

					InventoryMenu->PreDuplicationHighlight( ItemsToDuplicate );

					PlayerController->DisplayNotification( NSLOCTEXT( "", "", "Messenger is duplicating delivery items." ) );

					MissionStatus = EBotMissionStatus::DuplicatingItems;
				}
				else
				{
					PlayerController->DisplayNotification( NSLOCTEXT( "", "", "Messenger duplicates nothing." ) );

					MissionStatus = EBotMissionStatus::ExaminingItems;
				}
			}
		}
		else { UDevUtilities::PrintError( "Somehow Bot reaches the destination, but isn't in the target waypoint." ); }
	}
	else { UDevUtilities::PrintError( "Somehow Bot fails to reach the destination." ); }
}

void ABot::HandleOnInventoryMenuAdditionHighlightFinished()
{
	InventoryMenu->OnAdditionHighlightCompleted.RemoveDynamic( this, &ABot::HandleOnInventoryMenuAdditionHighlightFinished );

	switch ( MissionStatus )
	{
	case EBotMissionStatus::DuplicatingItems:
	case EBotMissionStatus::OpeningContainer:
	case EBotMissionStatus::UnlockingContainer:

		MissionStatus = EBotMissionStatus::ExaminingItems;

		break;

	}
}

void ABot::HandleOnInventoryMenuPreDuplicationHighlightFinished()
{
	InventoryMenu->OnPreDuplicationHighlightCompleted.RemoveDynamic( this, &ABot::HandleOnInventoryMenuPreDuplicationHighlightFinished );

	for ( UItemInfo* Item : ItemsToDuplicate )
	{
		Inventory->AddItem( Item->Duplicate() );
	}

	InventoryMenu->OnAdditionHighlightCompleted.AddDynamic( this, &ABot::HandleOnInventoryMenuAdditionHighlightFinished );
}

void ABot::HandleOnInventoryMenuContainerOpenHighlightFinished( UContainerItemInfo* Container )
{
	InventoryMenu->OnContainerOpenHighlightCompleted.RemoveDynamic( this, &ABot::HandleOnInventoryMenuContainerOpenHighlightFinished );

	Inventory->OpenItem( Container );

	InventoryMenu->OnAdditionHighlightCompleted.AddDynamic( this, &ABot::HandleOnInventoryMenuAdditionHighlightFinished );
}

void ABot::HandleOnInventoryMenuContainerUnlockHighlightFinished()
{
	InventoryMenu->OnContainerUnlockHighlightCompleted.RemoveDynamic( this, &ABot::HandleOnInventoryMenuContainerUnlockHighlightFinished );

	// Unlock.
	TArray<UItemInfo*> KeyAndContainer;
	KeyAndContainer.Add( KeyAndContainerToUnlockAfterHighlight.Key );
	KeyAndContainer.Add( KeyAndContainerToUnlockAfterHighlight.Value );
	Inventory->CombineItems( KeyAndContainer );

	InventoryMenu->OnAdditionHighlightCompleted.AddDynamic( this, &ABot::HandleOnInventoryMenuAdditionHighlightFinished );
}

void ABot::HandleOnInventoryMenuProceed()
{
	switch ( MissionStatus )
	{
	case EBotMissionStatus::CollectingItems:

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

		MissionStatus = EBotMissionStatus::DeliveringItems;

		InventoryMenu->HideInventory();

		StartMove();

		break;

	case EBotMissionStatus::ExaminingItems:

		ExamineItems();

		break;

	case EBotMissionStatus::ExaminationComplete:

		MissionStatus = EBotMissionStatus::DeliveringItems;

		InventoryMenu->HideInventory();

		StartMove();

		break;

	default:

		ensureAlwaysMsgf( false, TEXT( "What leads us here?" ) );

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
				if ( Container->IsOccupied() )
				{
					MissionStatus = EBotMissionStatus::OpeningContainer;

					InventoryMenu->OnContainerOpenHighlightCompleted.AddDynamic( this, &ABot::HandleOnInventoryMenuContainerOpenHighlightFinished ); 
					
					InventoryMenu->ContainerOpenHighlight( Container );

					PlayerController->DisplayNotification( NSLOCTEXT( "", "", "Messenger is opening a container." ) );

					// The released item from container may be a key to unlock other containers.
					// Eventually, HandleOnInventoryMenuAdditionHighlightFinished will call ExamineItems again.
					return;
				}
			}
			// A locked container
			else
			{
				for ( UItemInfo* SecondaryItem : ItemsToExamine )
				{
					if ( UKeyItemInfo* KeyItem = Cast<UKeyItemInfo>( SecondaryItem ) )
					{
						if ( KeyItem->GetKeyId() == Container->GetLockId() )
						{
							MissionStatus = EBotMissionStatus::UnlockingContainer;

							KeyAndContainerToUnlockAfterHighlight.Key = KeyItem;
							KeyAndContainerToUnlockAfterHighlight.Value = Container;

							InventoryMenu->OnContainerUnlockHighlightCompleted.AddDynamic( this, &ABot::HandleOnInventoryMenuContainerUnlockHighlightFinished );

							InventoryMenu->ContainerUnlockHighlight( KeyItem, Container );

							PlayerController->DisplayNotification( NSLOCTEXT( "", "", "Messenger is unlocking a container." ) );
							
							// The released item from container may be a key to unlock other containers.
							// Eventually, HandleOnInventoryMenuAdditionHighlightFinished will call ExamineItems again.
							return;
						}
					}
				}
			}
		}
	}

	PlayerController->DisplayNotification( NSLOCTEXT( "", "", "Messenger has finished tampering with items." ) );

	MissionStatus = EBotMissionStatus::ExaminationComplete;
}

bool ABot::ShouldDuplicate( UItemInfo* Item )
{
	if ( Cast<UKeyItemInfo>( Item ) )
	{
		return true;
	}
	else if ( Cast<UMessageItemInfo>( Item ) )
	{
		return true;
	}
	else if ( UContainerItemInfo* Container = Cast<UContainerItemInfo>( Item ) )
	{
		if ( Container->IsOccupied() )
		{
			UItemInfo* ContainedItem = Container->GetContainedItem();

			if ( Cast<UKeyItemInfo>( ContainedItem ) || Cast<UMessageItemInfo>( ContainedItem ) )
			{
				return true;
			}
		}
	}

	return false;
}
