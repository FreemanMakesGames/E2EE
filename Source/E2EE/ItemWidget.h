#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemWidget.generated.h"

class UImage;
class UTexture2D;

/**
 * 
 */
UCLASS()
class E2EE_API UItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION( BlueprintCallable )
	void UpdateImage( UTexture2D* NewTexture );

protected:

	// An Image widget holds a Texture.
	UPROPERTY( meta = ( BindWidget ) )
	UImage* Image_Icon;
	
};
