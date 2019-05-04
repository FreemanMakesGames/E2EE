#include "ItemClicker.h"

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

void UItemClicker::InsertItemWidget( UItemWidget* ItemWidget )
{
	if ( NamedSlot_ItemWidgetSlot->HasAnyChildren() )
	{
		UE_LOG( LogTemp, Warning, TEXT( "An ItemClicker's ItemWidget is being replaced. Is it intended?" ) );

		NamedSlot_ItemWidgetSlot->ClearChildren();
	}

	NamedSlot_ItemWidgetSlot->AddChild( ItemWidget );
}

void UItemClicker::HandleOnButtonClicked()
{
	OnClicked.Broadcast( this );
}
