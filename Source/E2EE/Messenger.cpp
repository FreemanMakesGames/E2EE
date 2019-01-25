// Fill out your copyright notice in the Description page of Project Settings.

#include "Messenger.h"

#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"

AMessenger::AMessenger()
{
	// Setup OnClicked event for the skeletal mesh component.
	MySkeletalMeshComponent = Cast<USkeletalMeshComponent>( GetComponentByClass( USkeletalMeshComponent::StaticClass() ) );
	MySkeletalMeshComponent->OnClicked.AddDynamic( this, &AMessenger::HandleOnClicked );
}

void AMessenger::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMessenger::SetupPlayerInputComponent( UInputComponent* PlayerInputComponent )
{
	Super::SetupPlayerInputComponent( PlayerInputComponent );

}

void AMessenger::HandleOnClicked( UPrimitiveComponent* TouchedComponent, FKey ButtonPressed )
{
	UE_LOG( LogTemp, Warning, TEXT( "Messenger is summoned." ) );
}
