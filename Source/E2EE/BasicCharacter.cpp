// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "BasicCharacter.h"

#include "GameUtilities.h"
#include "BasicPlayerController.h"
#include "Inventory.h"
#include "PlayerInventoryMenu.h"
#include "Item.h"
#include "HighlightComponent.h"
#include "Waypoint.h"
#include "PlayableCharacterMenu.h"
#include "Bot.h"
#include "DevUtilities.h"

#include "Engine/World.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraActor.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "Components/SkeletalMeshComponent.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Components/PrimitiveComponent.h"
#include "Components/WidgetComponent.h"

//////////////////////////////////////////////////////////////////////////
// AE2EECharacter

ABasicCharacter::ABasicCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	Inventory = CreateDefaultSubobject<UInventory>( TEXT( "Inventory" ) );

	PlayableCharacterMenuComponent = CreateDefaultSubobject<UWidgetComponent>( TEXT( "Playable Character Menu Component" ) );
	PlayableCharacterMenuComponent->SetupAttachment( RootComponent );
}

#pragma region Unreal Engine default input setup
void ABasicCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABasicCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABasicCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ABasicCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ABasicCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ABasicCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ABasicCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ABasicCharacter::OnResetVR);
}

void ABasicCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ABasicCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void ABasicCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void ABasicCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ABasicCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ABasicCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ABasicCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
#pragma endregion

void ABasicCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<ABasicPlayerController>( GetWorld()->GetFirstPlayerController() );

	GetCapsuleComponent()->OnClicked.AddDynamic( this, &ABasicCharacter::HandleOnCapsuleClicked );

	// Create InventoryMenu.
	if ( InventoryMenuClass )
	{
		InventoryMenu = CreateWidget<UPlayerInventoryMenu>( PlayerController, InventoryMenuClass );

		InventoryMenu->SetupInventory( Inventory );

		if ( !Username.IsEmpty() )
		{
			InventoryMenu->SetupTitle( FText::Format( NSLOCTEXT( "InventoryMenu", "InventoryMenuTitle", "{0}'s Inventory" ), Username ) );
		}
		else
		{
			InventoryMenu->SetupTitle( NSLOCTEXT( "InventoryMenu", "EmptyInventoryMenuTitle", "" ) );
		}
	}
	else { ensureAlways( false ); return; }

	// Create CharacterMenu.
	if ( PlayableCharacterMenuClass )
	{
		PlayableCharacterMenu = CreateWidget<UPlayableCharacterMenu>( PlayerController, PlayableCharacterMenuClass );
		PlayableCharacterMenu->SetOwnerCharacter( this );
		PlayableCharacterMenuComponent->SetWidget( PlayableCharacterMenu );
		PlayableCharacterMenu->SetVisibility( ESlateVisibility::Hidden );
	}
	else { ensureAlways( false ); return; }
}

#pragma region Getters and setters
UInventory* ABasicCharacter::GetInventory()
{
	return Inventory;
}

ETeam ABasicCharacter::GetTeam()
{
	return Team;
}

AWaypoint* ABasicCharacter::GetAssignedWaypoint()
{
	return AssignedWaypoint;
}

void ABasicCharacter::SetAssignedWaypoint( AWaypoint* InWaypoint )
{
	AssignedWaypoint = InWaypoint;
}

FText ABasicCharacter::GetUsername()
{
	return Username;
}
#pragma endregion

void ABasicCharacter::ShowInventory()
{
	InventoryMenu->ShowInventory();
}

void ABasicCharacter::PickUpItems()
{
	if ( !AssignedWaypoint ) { ensureAlways( false ); return; }

	TArray<AItem*> DroppedItems = AssignedWaypoint->GetDroppedItems();
	if ( DroppedItems.Num() > 0 )
	{
		for ( AItem* Item : DroppedItems )
		{
			Inventory->AddItem( Item->GetItemInfo() );

			Item->Destroy();
		}

		FText Notification = FText::Format( NSLOCTEXT( "BasicCharacter", "PickUpSucceed", "{0} has picked up the items." ), Username );
		PlayerController->DisplayNotification( Notification );
	}
	else
	{
		PlayerController->DisplayNotification( NSLOCTEXT( "BasicCharacter", "PickUpFailure", "There's nothing to pick up." ) );
	}
}

void ABasicCharacter::SendItems()
{
	if ( !Bot ) { ensureAlways( false ); return; }

	if ( AssignedWaypoint->GetDroppedItems().Num() > 0 )
	{
		Unfocus();

		Bot->Summon( this );
	}
	else
	{
		FText Notification = FText::Format( NSLOCTEXT( "BasicCharacter", "SendItemsFailure", "{0} has to drop some items before sending them." ), Username );
		PlayerController->DisplayNotification( Notification );
	}
}

void ABasicCharacter::Unfocus()
{
	PlayableCharacterMenu->Hide();

	PlayerController->SetViewTargetWithBlend( Camera_Overview, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic );
}

void ABasicCharacter::HandleOnCapsuleClicked( UPrimitiveComponent* TouchedComponent, FKey ButtonPressed )
{
	if ( !Camera_Focus ) { ensureAlways( false ); return; }

	PlayerController->SetViewTargetWithBlend( Camera_Focus, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic );

	PlayableCharacterMenu->Show();
}
