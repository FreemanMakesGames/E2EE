#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "KeyItem.generated.h"

class UKeyItemInfo;
class UKeyItemWidget;

class UStaticMeshComponent;
class UPickupComponent;
class UHighlightComponent;

/**
 * 
 */
UCLASS()
class E2EE_API AKeyItem : public AItem
{
	GENERATED_BODY()

public:

	AKeyItem();

protected:

	virtual void BeginPlay() override;

public:

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	UPickupComponent* PickupComponent;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	UHighlightComponent* HightlightComponent;

public:

	UFUNCTION( BlueprintCallable )
	void SetKeyId( int InKeyId );

	virtual UItemInfo* GetItemInfo() override;

	virtual UUserWidget* GetItemWidget() override;

protected:

	UPROPERTY()
	UKeyItemInfo* KeyItemInfo;

	UPROPERTY( BlueprintReadOnly )
	UKeyItemWidget* KeyItemWidget;
	
};
