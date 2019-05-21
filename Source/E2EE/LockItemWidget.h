#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LockItemWidget.generated.h"

class UImage;
class UTexture2D;
class UTextBlock;

/**
 * 
 */
UCLASS()
class E2EE_API ULockItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION( BlueprintCallable )
	void UpdateImage( UTexture2D* NewTexture );

	UFUNCTION( BlueprintCallable )
	void SetLockIdText( int InLockId );

protected:

	UPROPERTY( meta = ( BindWidget ) )
	UImage* Image_Icon;

	UPROPERTY( meta = ( BindWidget ) )
	UTextBlock* TextBlock_LockID;

};
