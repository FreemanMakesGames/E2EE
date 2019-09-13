// Fill out your copyright notice in the Description page of Project Settings.

#include "Bot.h"

#include "BotGameMode.h"
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
#include "DropItemComponent.h"
#include "DevUtilities.h"

#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "Runtime/Engine/Classes/AI/NavigationSystemBase.h"
#include "Runtime/AIModule/Classes/AIController.h"

ABot::ABot()
{
	PrimaryActorTick.bCanEverTick = true;

	Inventory = CreateDefaultSubobject<UInventory>( TEXT( "Inventory" ) );

	DropItemComponent = CreateDefaultSubobject<UDropItemComponent>( TEXT( "DropItemComponent" ) );
	DropItemComponent->SetupAttachment( GetCapsuleComponent() );

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
	if ( ButtonPressed == EKeys::LeftMouseButton )
	{
		Summon();
	}
	else if ( ButtonPressed == EKeys::RightMouseButton )
	{
		InventoryMenu->ShowInventory();
	}
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
						for ( AItem* Item : DroppedItems )
						{
							if ( UItemInfo* ItemInfo = Item->GetItemInfo() )
							{
								//Inventory->AddItem( ItemInfo );

								ItemsToDeliver.Add( ItemInfo );

								Item->Destroy();
							}
							else { ensureAlways( false ); return; }
						}

						InventoryMenu->SetupItemClickersForDelivery( ItemsToDeliver );

						InventoryMenu->ShowInventory();

						MissionStatus = EBotMissionStatus::CollectionComplete;

						PlayerController->DisplayNotification( NSLOCTEXT( "", "", "Messenger has collected the items." ) );
					}
					else
					{
						PlayerController->DisplayNotification( NSLOCTEXT( "", "", "Messenger doesn't find any item to collect." ) );

						MissionStatus = EBotMissionStatus::Idle;
					}
				}
				// If on the way to deliver items, drop off the delivery.
				else if ( MissionStatus == EBotMissionStatus::DeliveringItems )
				{
					// TODO: Extract method.

					CurrentWaypoint->DropMultipleItems( ItemsToDeliver );

					InventoryMenu->ClearItemClickersForDelivery( ItemsToDeliver );

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

					PlayerController->DisplayNotification( NSLOCTEXT( "", "", "Messenger is saving copies of the delivery." ) );

					MissionStatus = EBotMissionStatus::DuplicatingItems;
				}
				else
				{
					PlayerController->DisplayNotification( NSLOCTEXT( "", "", "Messenger finds nothing worthwhile to save copies from." ) );

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
	case EBotMissionStatus::CollectionComplete:

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

	case EBotMissionStatus::Idle:

		InventoryMenu->HideInventory();

		break;

	default:

		ensureAlwaysMsgf( false, TEXT( "What leads us here?" ) );

	}
}

void ABot::Summon()
{
	UDevUtilities::PrintInfo( "Messenger is being summoned." );

	// Don't move if there's no active character.
	if ( ABasicCharacter* ActiveCharacter = PlayerController->GetActiveCharacter() )
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

	for ( UItemInfo* Item : Inventory->GetItems() )
	{
		if ( UMessageItemInfo* Message = Cast<UMessageItemInfo>( Item ) )
		{
			//GetWorld()->GetAuthGameMode<ABotGameMode>()->ReadMessage( this ); // Assume ABotGameMode has to exist if Bot exists.

			Inventory->ReadItem( Item );
		}
		else if ( UContainerItemInfo* Container = Cast<UContainerItemInfo>( Item ) )
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
				for ( UItemInfo* SecondaryItem : Inventory->GetItems() )
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

bool ABot::ShouldDuplicate( UItemInfo* TargetItem )
{
	for ( UItemInfo* ExistingItem : Inventory->GetItems() )
	{
		if ( TargetItem->IsEquivalentTo( ExistingItem ) ) { return false; }
	}

	if ( UKeyItemInfo* TargetKey = Cast<UKeyItemInfo>( TargetItem ) )
	{
		return !AlreadyOwnsSuchKey( TargetKey );
	}
	else if ( UContainerItemInfo* TargetContainer = Cast<UContainerItemInfo>( TargetItem ) )
	{
		if ( TargetContainer->IsOccupied() )
		{
			UItemInfo* TargetContainedItem = TargetContainer->GetContainedItem();

			if ( UKeyItemInfo* TargetContainedKey = Cast<UKeyItemInfo>( TargetContainedItem ) )
			{
				return !AlreadyOwnsSuchKey( TargetContainedKey );
			}
			else if ( Cast<UMessageItemInfo>( TargetContainedItem ) )
			{
				return true;
			}
		}
	}
	else if ( Cast<UMessageItemInfo>( TargetItem ) )
	{
		return true;
	}

	return false;
}

bool ABot::AlreadyOwnsSuchKey( UKeyItemInfo* Key )
{
	for ( UItemInfo* ExistingItem : Inventory->GetItems() )
	{
		if ( Key->IsEquivalentTo( ExistingItem ) ) { return true; }
	}

	return false;
}
