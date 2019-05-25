#include "MessageItemWidget.h"

#include "MessageItemInfo.h"
#include "DevUtilities.h"

#include "Components/Image.h"
#include "Engine/Texture2D.h"

void UMessageItemWidget::SetItemInfo( UItemInfo* InItemInfo )
{
	MessageItemInfo = Cast<UMessageItemInfo>( InItemInfo );
	if ( MessageItemInfo )
	{

	}
	else
	{
		UDevUtilities::PrintError( "UMessageItemWidget::SetItemInfo gets a non-MessageItemInfo!" );
	}
}

void UMessageItemWidget::UpdateImage( UTexture2D* NewTexture )
{
	Image_Icon->SetBrushFromTexture( NewTexture );
}
