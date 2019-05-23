#pragma once

#include "CoreMinimal.h"
#include "ItemWidget.h"
#include "MessageItemWidget.generated.h"

class UItemInfo;
class UMessageItemInfo;
class UImage;
class UTexture2D;

/**
 * 
 */
UCLASS()
class E2EE_API UMessageItemWidget : public UItemWidget
{
	GENERATED_BODY()

public:

	virtual void SetItemInfo( UItemInfo* InItemInfo ) override;

protected:

	UPROPERTY( meta = ( BindWidget ) )
	UImage* Image_Icon;

	UPROPERTY( VisibleInstanceOnly, BlueprintReadWrite )
	UMessageItemInfo* MessageItemInfo;

public:

	UFUNCTION( BlueprintCallable )
	void UpdateImage( UTexture2D* NewTexture );
	
};
