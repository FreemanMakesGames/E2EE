#include "LockItemWidget.h"

#include "LockItemInfo.h"
#include "DevUtilities.h"

#include "Components/Image.h"
#include "Engine/Texture2D.h"
#include "Components/TextBlock.h"

void ULockItemWidget::SetItemInfo( UItemInfo* InItemInfo )
{
	LockItemInfo = Cast<ULockItemInfo>( InItemInfo );
	if ( LockItemInfo )
	{
		FText Text = FText::FromString( FString::FromInt( LockItemInfo->GetLockId() ) );

		TextBlock_LockId->SetText( Text );
	}
	else
	{
		UDevUtilities::PrintError( "ULockItemWidget::SetItemInfo gets a non-LockItemInfo!" );
	}
}

void ULockItemWidget::UpdateImage( UTexture2D* NewTexture )
{
	Image_Icon->SetBrushFromTexture( NewTexture );
}
