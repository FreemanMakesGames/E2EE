#include "ItemClicker.h"

#include "Components/Button.h"
#include "Components/NamedSlot.h"

UItemClicker::UItemClicker( const FObjectInitializer& ObjectInitializer ) : Super( ObjectInitializer )
{

}

void UItemClicker::NativeOnInitialized()
{
	Button_Clicker->OnClicked.AddDynamic( this, &UItemClicker::HandleOnButtonClicked );
}

UNamedSlot* UItemClicker::GetItemWidgetSlot()
{
	return NamedSlot_ItemWidgetSlot;
}

void UItemClicker::HandleOnButtonClicked()
{
	OnClicked.Broadcast( this );
}
