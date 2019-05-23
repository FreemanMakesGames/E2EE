#include "MessageItemWidget.h"

#include "MessageItemInfo.h"

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

	}
}

void UMessageItemWidget::UpdateImage( UTexture2D* NewTexture )
{
	Image_Icon->SetBrushFromTexture( NewTexture );
}
