#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ContainerItemWidget.generated.h"

class UImage;
class UTexture2D;

/**
 *
 */
UCLASS()
class E2EE_API UContainerItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION( BlueprintCallable )
	void UpdateImage( UTexture2D* NewTexture );

protected:

	UPROPERTY( meta = ( BindWidget ) )
	UImage* Image_Icon;

};
