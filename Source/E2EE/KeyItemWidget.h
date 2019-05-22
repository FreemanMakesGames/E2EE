#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KeyItemWidget.generated.h"

class UImage;
class UTexture2D;
class UTextBlock;

/**
 *
 */
UCLASS()
class E2EE_API UKeyItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION( BlueprintCallable )
	void UpdateImage( UTexture2D* NewTexture );

	UFUNCTION( BlueprintCallable )
	void SetKeyIdText( int InKeyId );

protected:

	UPROPERTY( meta = ( BindWidget ) )
	UImage* Image_Icon;

	UPROPERTY( meta = ( BindWidget ) )
	UTextBlock* TextBlock_KeyId;

};
