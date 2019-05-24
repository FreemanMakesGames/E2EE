#include "ItemClicker.h"

#include "ItemInfo.h"
#include "ItemWidget.h"
#include "ItemDefinitionList.h"
#include "BasicGameState.h"

#include "Components/Button.h"
#include "Components/NamedSlot.h"

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

	if ( NamedSlot_ItemWidgetSlot->HasAnyChildren() )
	{
		UE_LOG( LogTemp, Warning, TEXT( "An ItemClicker's Item is being replaced. Is it intended?" ) );

		NamedSlot_ItemWidgetSlot->ClearChildren();
	}

	TSubclassOf<UItemWidget> ItemWidgetClass = GetWorld()->GetGameState<ABasicGameState>()->GetItemDefinitionList()->TypeIdToItemWidgetClass[ItemInfo->GetItemTypeId()];

	UItemWidget* ItemWidget = CreateWidget<UItemWidget>( this, ItemWidgetClass );
	
	NamedSlot_ItemWidgetSlot->AddChild( ItemWidget );
}

void UItemClicker::HandleOnButtonClicked()
{
	OnClicked.Broadcast( this );
}
