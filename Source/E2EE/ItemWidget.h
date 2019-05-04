#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemWidget.generated.h"

class UImage;

/**
 * 
 */
UCLASS()
class E2EE_API UItemWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	// An Image holds a Texture.
	UPROPERTY( meta = ( BindWidget ) )
	UImage* Image_Icon;
	
};
