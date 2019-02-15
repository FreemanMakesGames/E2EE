// Fill out your copyright notice in the Description page of Project Settings.

#include "HighlightComponent.h"

#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Engine/StaticMesh.h"
#include "Classes/Materials/MaterialInterface.h"

void UHighlightComponent::Highlight( UPrimitiveComponent* ComponentToHighlight )
{
	ComponentToHighlight->SetRenderCustomDepth( true );
}

void UHighlightComponent::EndHighlight( UPrimitiveComponent* ComponentToEndHighlight )
{
	ComponentToEndHighlight->SetRenderCustomDepth( false );
}
