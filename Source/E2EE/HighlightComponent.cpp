// Fill out your copyright notice in the Description page of Project Settings.

#include "HighlightComponent.h"

#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Engine/StaticMesh.h"
#include "Classes/Materials/MaterialInterface.h"

// Sets default values for this component's properties
UHighlightComponent::UHighlightComponent()
{
	//PrimaryComponentTick.bCanEverTick = true;

	/*TArray<UStaticMeshComponent*> StaticMeshComponents;
	if ( GetOwner() )
	{
		GetOwner()->GetComponents<UStaticMeshComponent>( StaticMeshComponents );

		UStaticMeshComponent* StaticMeshComponent;
		if ( StaticMeshComponents.Num() > 0 )
		{
			StaticMeshComponent = StaticMeshComponents[ 0 ];

			StaticMeshComponent->OnBeginCursorOver.AddDynamic( this, &UHighlightComponent::Highlight );
			StaticMeshComponent->OnEndCursorOver.AddDynamic( this, &UHighlightComponent::EndHighlight );
		}
	}*/
	if ( GetOwner() )
	{
		UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>( GetOwner()->GetComponentByClass( UStaticMeshComponent::StaticClass() ) );
		if ( StaticMeshComponent )
		{
			StaticMeshComponent->OnBeginCursorOver.AddDynamic( this, &UHighlightComponent::Highlight );
			StaticMeshComponent->OnEndCursorOver.AddDynamic( this, &UHighlightComponent::EndHighlight );
		}
	}
}


// Called when the game starts
void UHighlightComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UHighlightComponent::Highlight( UPrimitiveComponent* TouchedComponent )
{
	UE_LOG( LogTemp, Warning, TEXT( "UHighlightComponent: Cursor on %s" ), *TouchedComponent->GetName() );

	//GetWorld()->GetFirstPlayerController()->SetMouseCursorWidget( EMouseCursor::Hand, CursorWidget );

	UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>( TouchedComponent );
	StaticMeshComponent->SetRenderCustomDepth( true );
}

void UHighlightComponent::EndHighlight( UPrimitiveComponent* TouchedComponent )
{
	UE_LOG( LogTemp, Warning, TEXT( "UHighlightComponent: Cursor off %s" ), *TouchedComponent->GetName() );

	//GetWorld()->GetFirstPlayerController()->SetMouseCursorWidget( EMouseCursor::Hand, CursorWidget );

	UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>( TouchedComponent );
	StaticMeshComponent->SetRenderCustomDepth( false );
}


// Called every frame
void UHighlightComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

