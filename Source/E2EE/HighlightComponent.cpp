// Fill out your copyright notice in the Description page of Project Settings.

#include "HighlightComponent.h"

#include "Components/PrimitiveComponent.h"

void UHighlightComponent::BeginPlay()
{
	Super::BeginPlay();

	if ( !TargetPrimitiveComponent )
	{
		TargetPrimitiveComponent = GetOwner()->FindComponentByClass<UPrimitiveComponent>();
	}

	if ( TargetPrimitiveComponent )
	{
		TargetPrimitiveComponent->OnBeginCursorOver.AddDynamic( this, &UHighlightComponent::Highlight );
		TargetPrimitiveComponent->OnEndCursorOver.AddDynamic( this, &UHighlightComponent::EndHighlight );
	}
	else
	{
		UE_LOG( LogTemp, Error, TEXT( "This Highlight Component's owner doesn't have a Primitive Component!" ) );
	}
}

void UHighlightComponent::Highlight( UPrimitiveComponent* Target )
{
	if ( Target )
	{
		Target->SetRenderCustomDepth( true );
	}
}

void UHighlightComponent::EndHighlight( UPrimitiveComponent* Target )
{
	if ( Target )
	{
		Target->SetRenderCustomDepth( false );
	}
}

