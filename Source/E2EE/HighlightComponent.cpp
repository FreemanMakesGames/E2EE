// Fill out your copyright notice in the Description page of Project Settings.

#include "HighlightComponent.h"

#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Engine/StaticMesh.h"
#include "Classes/Materials/MaterialInterface.h"

UHighlightComponent::UHighlightComponent()
{
	if ( GetOwner() )
	{
		UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>( GetOwner()->GetComponentByClass( UPrimitiveComponent::StaticClass() ) );
		if ( PrimitiveComponent )
		{
			PrimitiveComponent->OnBeginCursorOver.AddDynamic( this, &UHighlightComponent::Highlight );
			PrimitiveComponent->OnEndCursorOver.AddDynamic( this, &UHighlightComponent::EndHighlight );
		}
	}
}

void UHighlightComponent::Highlight( UPrimitiveComponent* TouchedComponent )
{
	//UE_LOG( LogTemp, Display, TEXT( "HighlightComponent: Cursor on %s" ), *TouchedComponent->GetName() );

	//GetWorld()->GetFirstPlayerController()->SetMouseCursorWidget( EMouseCursor::Hand, CursorWidget );

	TouchedComponent->SetRenderCustomDepth( true );
}

void UHighlightComponent::EndHighlight( UPrimitiveComponent* TouchedComponent )
{
	//UE_LOG( LogTemp, Display, TEXT( "HighlightComponent: Cursor off %s" ), *TouchedComponent->GetName() );

	//GetWorld()->GetFirstPlayerController()->SetMouseCursorWidget( EMouseCursor::Hand, CursorWidget );

	TouchedComponent->SetRenderCustomDepth( false );
}
