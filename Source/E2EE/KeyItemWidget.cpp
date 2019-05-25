#include "KeyItemWidget.h"

#include "KeyItemInfo.h"
#include "DevUtilities.h"

#include "Components/Image.h"
#include "Engine/Texture2D.h"
#include "Components/TextBlock.h"

void UKeyItemWidget::SetItemInfo( UItemInfo* InItemInfo )
{
	KeyItemInfo = Cast<UKeyItemInfo>( InItemInfo );
	if ( KeyItemInfo )
	{
		FText Text = FText::FromString( FString::FromInt( KeyItemInfo->GetKeyId() ) );

		TextBlock_KeyId->SetText( Text );
	}
	else
	{
		UDevUtilities::PrintError( "UKeyItemWidget::SetItemInfo gets a non-KeyItemInfo!" );
	}
}

void UKeyItemWidget::UpdateImage( UTexture2D* NewTexture )
{
	Image_Icon->SetBrushFromTexture( NewTexture );
}
