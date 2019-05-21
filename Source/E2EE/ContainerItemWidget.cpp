#include "ContainerItemWidget.h"

#include "Components/Image.h"
#include "Engine/Texture2D.h"

void UContainerItemWidget::UpdateImage( UTexture2D* NewTexture )
{
	Image_Icon->SetBrushFromTexture( NewTexture );
}
