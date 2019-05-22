#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LockItemWidget.generated.h"

class UItemInfo;
class ULockItemInfo;
class UImage;
class UTexture2D;
class UTextBlock;

/**
 * 
 */
UCLASS()
class E2EE_API ULockItemWidget : public UItemWidget
{
	GENERATED_BODY()

public:

	virtual void SetItemInfo( UItemInfo* InItemInfo ) override;

protected:

	UPROPERTY( meta = ( BindWidget ) )
	UImage* Image_Icon;

	UPROPERTY( meta = ( BindWidget ) )
	UTextBlock* TextBlock_LockId;

	UPROPERTY( VisibleInstanceOnly, BlueprintReadWrite )
	ULockItemInfo* LockItemInfo;

public:

	UFUNCTION( BlueprintCallable )
	void UpdateImage( UTexture2D* NewTexture );

};
