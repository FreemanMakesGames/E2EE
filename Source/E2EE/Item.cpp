#include "Item.h"

#include "GameUtilities.h"
#include "ItemWidget.h"

#include "Net/UnrealNetwork.h"

AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	bAlwaysRelevant = true;
	NetDormancy = ENetDormancy::DORM_Never;

	bIsActive = true;
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
	ItemWidget = CreateWidget<UItemWidget>( GetWorld()->GetFirstPlayerController(), ItemWidgetClass );
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AItem::SetIsActive( bool IsActive )
{
	bIsActive = IsActive;

	if ( bIsActive )
	{
		UGameUtilities::EnableActor( this );
	}
	else
	{
		UGameUtilities::DisableActor( this );
	}
}

TArray<EItemUsage> AItem::GetItemUsages()
{
	return ItemUsages;
}

UItemWidget* AItem::GetItemWidget()
{
	return ItemWidget;
}

void AItem::SetItemWidget( UItemWidget* ItemWidgetToSet )
{
	ItemWidget = ItemWidgetToSet;
}

void AItem::OnRep_IsActive()
{
	if ( bIsActive )
	{
		UGameUtilities::EnableActor( this );
	}
	else
	{
		UGameUtilities::DisableActor( this );
	}
}

void AItem::GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );

	DOREPLIFETIME( AItem, bIsActive );
}
