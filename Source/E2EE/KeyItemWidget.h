#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KeyItemWidget.generated.h"

class UItemInfo;
class UKeyItemInfo;
class UImage;
class UTexture2D;
class UTextBlock;

/**
 *
 */
UCLASS()
class E2EE_API UKeyItemWidget : public UItemWidget
{
	GENERATED_BODY()

public:

	virtual void SetItemInfo( UItemInfo* InItemInfo ) override;

protected:

	UPROPERTY( meta = ( BindWidget ) )
	UImage* Image_Icon;

	UPROPERTY( meta = ( BindWidget ) )
	UTextBlock* TextBlock_KeyId;

	UPROPERTY( VisibleInstanceOnly, BlueprintReadWrite )
	UKeyItemInfo* KeyItemInfo;

public:

	UFUNCTION( BlueprintCallable )
	void UpdateImage( UTexture2D* NewTexture );

};
