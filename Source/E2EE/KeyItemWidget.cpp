#include "KeyItemWidget.h"

#include "Components/Image.h"
#include "Engine/Texture2D.h"
#include "Components/TextBlock.h"

void UKeyItemWidget::UpdateImage( UTexture2D* NewTexture )
{
	Image_Icon->SetBrushFromTexture( NewTexture );
}

void UKeyItemWidget::SetKeyIdText( int InKeyId )
{
	FText Text = FText::FromString( FString::FromInt( InKeyId ) );

	TextBlockKey_KeyID->SetText( Text );
}
