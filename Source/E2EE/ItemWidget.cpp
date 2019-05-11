#include "ItemWidget.h"

#include "Components/Image.h"
#include "Engine/Texture2D.h"

void UItemWidget::UpdateImage( UTexture2D* NewTexture )
{
	Image_Icon->SetBrushFromTexture( NewTexture );
}
