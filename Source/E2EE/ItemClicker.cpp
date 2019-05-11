#include "ItemClicker.h"

#include "Item.h"
#include "ItemWidget.h"

#include "Components/Button.h"
#include "Components/NamedSlot.h"

UItemClicker::UItemClicker( const FObjectInitializer& ObjectInitializer ) : Super( ObjectInitializer )
{

}

void UItemClicker::NativeOnInitialized()
{
	Button_Clicker->OnClicked.AddDynamic( this, &UItemClicker::HandleOnButtonClicked );
}

AItem* UItemClicker::GetItem()
{
	return Item;
}

void UItemClicker::SetItem( AItem* ItemToSet )
{
	Item = ItemToSet;

	if ( NamedSlot_ItemWidgetSlot->HasAnyChildren() )
	{
		UE_LOG( LogTemp, Warning, TEXT( "An ItemClicker's Item is being replaced. Is it intended?" ) );

		NamedSlot_ItemWidgetSlot->ClearChildren();
	}

	NamedSlot_ItemWidgetSlot->AddChild( Item->GetItemWidget() );
}

void UItemClicker::HandleOnButtonClicked()
{
	OnClicked.Broadcast( this );
}
