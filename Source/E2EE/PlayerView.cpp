// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerView.h"

#include "Engine/Classes/Camera/CameraComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
// Sets default values
APlayerView::APlayerView()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>( TEXT( "Camera Component" ) );
	RootComponent = CameraComponent;
}

// Called when the game starts or when spawned
void APlayerView::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APlayerView::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerView::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

