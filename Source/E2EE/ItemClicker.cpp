#include "ItemClicker.h"

#include "ItemInfo.h"
#include "ItemWidget.h"
#include "ItemDefinitionList.h"
#include "BasicGameState.h"
#include "DevUtilities.h"

#include "Components/Button.h"
#include "Components/NamedSlot.h"
#include "Kismet/GameplayStatics.h"

UItemClicker::UItemClicker( const FObjectInitializer& ObjectInitializer ) : Super( ObjectInitializer )
{

}

void UItemClicker::NativeOnInitialized()
{
	Button_Clicker->OnClicked.AddDynamic( this, &UItemClicker::HandleOnButtonClicked );
}

UItemInfo* UItemClicker::GetItemInfo()
{
	return ItemInfo;
}

void UItemClicker::SetItemInfo( UItemInfo* ItemToSet )
{
	ItemInfo = ItemToSet;

	// Check and clear Named Slot's content.
	if ( NamedSlot_ItemWidgetSlot->HasAnyChildren() )
	{
		UE_LOG( LogTemp, Warning, TEXT( "An ItemClicker's Item is being replaced. Is it intended?" ) );

		NamedSlot_ItemWidgetSlot->ClearChildren();
	}

	// Get Item Widget class through Game State.
	ABasicGameState* GameState = Cast<ABasicGameState>( UGameplayStatics::GetGameState( GetWorld() ) );
	AItemDefinitionList* ItemDefinitionList = GameState->GetItemDefinitionList();
	int ItemTypeId = ItemInfo->GetItemTypeId();
	TSubclassOf<UItemWidget>* ItemWidgetClass = ItemDefinitionList->TypeIdToItemWidgetClass.Find( ItemTypeId );

	if ( ItemWidgetClass )
	{
		UItemWidget* ItemWidget = CreateWidget<UItemWidget>( this, *ItemWidgetClass );

		NamedSlot_ItemWidgetSlot->AddChild( ItemWidget );
	}
	else
	{
		UDevUtilities::PrintError( "UItemClicker::SetItemInfo gets a UItemInfo whose Type ID doesn't match any UItemWidget class in the definition list." );
	}
}

void UItemClicker::HandleOnButtonClicked()
{
	OnClicked.Broadcast( this );
}
