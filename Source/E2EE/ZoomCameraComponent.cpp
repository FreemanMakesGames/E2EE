// Fill out your copyright notice in the Description page of Project Settings.

#include "ZoomCameraComponent.h"

#include "Components/PrimitiveComponent.h"
#include "InputCore/Classes/InputCoreTypes.h"

UZoomCameraComponent::UZoomCameraComponent()
{
	TArray<UPrimitiveComponent*> PrimitiveComponents;
	if ( GetOwner() )
	{
		GetOwner()->GetComponents<UPrimitiveComponent>( PrimitiveComponents );

		UPrimitiveComponent* PrimitiveComponent;
		if ( PrimitiveComponents.Num() > 0 )
		{
			PrimitiveComponent = PrimitiveComponents[ 0 ];

			PrimitiveComponent->OnClicked.AddDynamic( this, &UZoomCameraComponent::ZoomIn );
		}
	}
	
}

void UZoomCameraComponent::ZoomIn( UPrimitiveComponent* TouchedComponent, FKey ButtonPressed )
{
	UE_LOG( LogTemp, Warning, TEXT( "Clicked on %s" ), *TouchedComponent->GetName() );
}
