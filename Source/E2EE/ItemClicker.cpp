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

void UItemClicker::SetItemInfo( UItemInfo* InItemInfo )
{
	ItemInfo = InItemInfo;

	// Check and clear Named Slot's content.
	if ( NamedSlot_ItemWidgetSlot->HasAnyChildren() )
	{
		UE_LOG( LogTemp, Warning, TEXT( "An ItemClicker's Item is being replaced. Is it intended?" ) );

		NamedSlot_ItemWidgetSlot->ClearChildren();
	}

	UItemWidget* ItemWidget = CreateWidget<UItemWidget>( this, ItemInfo->GetItemWidgetClass() );
	ItemWidget->SetItemInfo( ItemInfo );

	NamedSlot_ItemWidgetSlot->AddChild( ItemWidget );
}

void UItemClicker::HandleOnButtonClicked()
{
	OnClicked.Broadcast( this );
}
