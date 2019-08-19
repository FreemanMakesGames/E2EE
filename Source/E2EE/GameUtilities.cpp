#include "GameUtilities.h"

#include "BasicPlayerController.h"

#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"

# pragma region Actor Disabling/Enabling
void UGameUtilities::DisableActor( AActor* TargetActor )
{
	TargetActor->SetActorHiddenInGame( true );
	TargetActor->SetActorTickEnabled( false );
	TargetActor->SetActorEnableCollision( false );

	UPrimitiveComponent* PrimitiveComponent = TargetActor->FindComponentByClass<UPrimitiveComponent>();
	if ( PrimitiveComponent )
	{
		PrimitiveComponent->SetSimulatePhysics( false );
		PrimitiveComponent->SetHiddenInGame( true );
		PrimitiveComponent->SetComponentTickEnabled( false );
		PrimitiveComponent->SetCollisionEnabled( ECollisionEnabled::NoCollision );
		PrimitiveComponent->SetGenerateOverlapEvents( false );
	}
}

void UGameUtilities::EnableActor( AActor* TargetActor )
{
	TargetActor->SetActorHiddenInGame( false );
	TargetActor->SetActorTickEnabled( true );
	TargetActor->SetActorEnableCollision( true );

	UPrimitiveComponent* PrimitiveComponent = TargetActor->FindComponentByClass<UPrimitiveComponent>();
	if ( PrimitiveComponent )
	{
		PrimitiveComponent->SetSimulatePhysics( true );
		PrimitiveComponent->SetHiddenInGame( false );
		PrimitiveComponent->SetComponentTickEnabled( true );
		PrimitiveComponent->SetCollisionEnabled( ECollisionEnabled::QueryAndPhysics );
		PrimitiveComponent->SetGenerateOverlapEvents( true );
	}
}

void UGameUtilities::ToggleActor( AActor* TargetActor, bool ToggleOn )
{
	if ( ToggleOn )
	{
		EnableActor( TargetActor );
	}
	else
	{
		DisableActor( TargetActor );
	}
}

# pragma endregion
