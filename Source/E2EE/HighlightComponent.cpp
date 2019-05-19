// Fill out your copyright notice in the Description page of Project Settings.

#include "HighlightComponent.h"

#include "Components/PrimitiveComponent.h"

void UHighlightComponent::BeginPlay()
{
	Super::BeginPlay();

	UPrimitiveComponent* PrimitiveComponent = GetOwner()->FindComponentByClass<UPrimitiveComponent>();

	if ( PrimitiveComponent )
	{
		PrimitiveComponent->OnBeginCursorOver.AddDynamic( this, &UHighlightComponent::Highlight );
		PrimitiveComponent->OnEndCursorOver.AddDynamic( this, &UHighlightComponent::EndHighlight );
	}
	else
	{
		UE_LOG( LogTemp, Error, TEXT( "This Highlight Component's owner doesn't have a Primitive Component!" ) );
	}
}

void UHighlightComponent::Highlight( UPrimitiveComponent* ComponentToHighlight )
{
	if ( ComponentToHighlight )
	{
		ComponentToHighlight->SetRenderCustomDepth( true );
	}
}

void UHighlightComponent::EndHighlight( UPrimitiveComponent* ComponentToEndHighlight )
{
	if ( ComponentToEndHighlight )
	{
		ComponentToEndHighlight->SetRenderCustomDepth( false );
	}
}

