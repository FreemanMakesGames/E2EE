#include "LockItemWidget.h"

#include "Components/Image.h"
#include "Engine/Texture2D.h"
#include "Components/TextBlock.h"

void ULockItemWidget::UpdateImage( UTexture2D* NewTexture )
{
	Image_Icon->SetBrushFromTexture( NewTexture );
}

void ULockItemWidget::SetLockIdText( int InLockId )
{
	FText Text = FText::FromString( FString::FromInt( InLockId ) );

	TextBlock_LockId->SetText( Text );
}
