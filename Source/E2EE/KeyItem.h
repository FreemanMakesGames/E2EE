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
 * It is named KeyItem because a class named "Key" already exists...
 */
UCLASS()
class E2EE_API AKeyItem : public AItem
{
	GENERATED_BODY()

public:

	AKeyItem( const FObjectInitializer& ObjectInitializer );

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

	virtual UItemInfo* GetItemInfo() override;

	UFUNCTION( BlueprintCallable )
	int GetKeyId();

	UFUNCTION( BlueprintCallable )
	void SetKeyId( int InKeyId );

protected:

	UPROPERTY()
	UKeyItemInfo* KeyItemInfo;
	
};
