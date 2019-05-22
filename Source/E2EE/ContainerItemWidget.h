#pragma once

#include "CoreMinimal.h"
#include "ItemWidget.h"
#include "ContainerItemWidget.generated.h"

class UItemInfo;
class UContainerItemInfo;
class UImage;
class UTexture2D;

/**
 *
 */
UCLASS()
class E2EE_API UContainerItemWidget : public UItemWidget
{
	GENERATED_BODY()

public:

	virtual void SetItemInfo( UItemInfo* InItemInfo ) override;

protected:

	UPROPERTY( VisibleInstanceOnly, BlueprintReadWrite )
	UContainerItemInfo* ContainerItemInfo;

	UPROPERTY( meta = ( BindWidget ) )
	UImage* Image_Icon;

public:

	UFUNCTION( BlueprintCallable )
	void UpdateImage( UTexture2D* NewTexture );

protected:

	UFUNCTION( BlueprintImplementableEvent )
	void HandleOnOccupied();

	UFUNCTION( BlueprintImplementableEvent )
	void HandleOnVacated();

	UFUNCTION( BlueprintImplementableEvent )
	void HandleOnLocked();

	UFUNCTION( BlueprintImplementableEvent )
	void HandleOnUnlocked();

};
