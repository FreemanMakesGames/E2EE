#include "Inventory.h"

#include "ContainerItemInfo.h"
#include "ItemCombiner.h"
#include "DropItemComponent.h"
#include "BasicCharacter.h"
#include "BasicPlayerController.h"
#include "DevUtilities.h"

#include "Engine/World.h"
#include "Net/UnrealNetwork.h"

UInventory::UInventory( const FObjectInitializer& ObjectInitializer ) : Super( ObjectInitializer )
{
	
}

void UInventory::BeginPlay()
{
	Super::BeginPlay();

	ItemCombiner = NewObject<UItemCombiner>();
	ItemCombiner->SetPlayerController( Cast<ABasicPlayerController>( GetWorld()->GetFirstPlayerController() ) );
}

TArray<UItemInfo*> UInventory::GetItems()
{
	return Items;
}

int UInventory::CountItems()
{
	return Items.Num();
}

void UInventory::AddItem( UItemInfo* ItemToAdd )
{
	ensureAlways( ItemToAdd );

	Items.Add( ItemToAdd );

	OnItemAdded.Broadcast( ItemToAdd );
}

void UInventory::RemoveItem( UItemInfo* ItemToRemove )
{
	Items.Remove( ItemToRemove );

	OnItemRemoved.Broadcast( ItemToRemove );
}

void UInventory::DropItem( UItemInfo* ItemToDrop )
{
	UDropItemComponent* DropItemComponent = GetOwner()->FindComponentByClass<UDropItemComponent>();

	if ( DropItemComponent )
	{
		DropItemComponent->ServerDropItem( ItemToDrop );
	}
	else
	{
		ensureMsgf( false, TEXT( "The owner of this UInventory doesn't have a UDropItemComponent! Aborted." ) );
		return;
	}

	RemoveItem( ItemToDrop );
}

void UInventory::ServerDuplicateItem_Implementation( UItemInfo* TargetItem )
{
	MulticastDuplicateItem( TargetItem );
}

bool UInventory::ServerDuplicateItem_Validate( UItemInfo* TargetItem )
{
	return true;
}

void UInventory::MulticastDuplicateItem_Implementation( UItemInfo* TargetItem )
{
	AddItem( TargetItem->Duplicate() );
}

void UInventory::OpenItem( UItemInfo* TargetItem )
{
	UContainerItemInfo* Container = Cast<UContainerItemInfo>( TargetItem );
	if ( Container )
	{
		// Player controller for notification
		ABasicPlayerController* PlayerController = Cast<ABasicPlayerController>( GetWorld()->GetFirstPlayerController() );

		if ( Container->IsLocked() )
		{
			FFormatNamedArguments Args;
			Args.Add( "Lock ID", Container->GetLockId() );
			PlayerController->DisplayNotification( FText::Format( NSLOCTEXT( "", "", "This container is locked by lock #{Lock ID}" ), Args ) );

			return;
		}

		if ( !Container->IsOccupied() )
		{
			PlayerController->DisplayNotification( NSLOCTEXT( "", "", "This container is empty!" ) );

			return;
		}

		AddItem( Container->ReleaseItem() );
	}
	else
	{
		ensureAlwaysMsgf( false, TEXT( "How can a non-Container have the option to open?" ) );
	}
}

void UInventory::ReadItem( UItemInfo* ItemToRead )
{
	ABasicCharacter* Owner = Cast<ABasicCharacter>( GetOwner() );
	if ( Owner )
	{
		Owner->ReadItem( ItemToRead );
	}
	else
	{
		ensureAlwaysMsgf( false, TEXT( "Inventory not owned by characters isn't implemented." ) );
	}
}

void UInventory::CombineItems( TArray<UItemInfo*> SourceItems )
{
	TArray<UItemInfo*> ResultItems = ItemCombiner->CombineItems( SourceItems );

	for ( UItemInfo* Item : SourceItems )
	{
		RemoveItem( Item );
	}

	for ( UItemInfo* Item : ResultItems )
	{
		AddItem( Item );
	}
}

void UInventory::GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );

	DOREPLIFETIME( UInventory, Items );
}
