#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemClicker.generated.h"

class AItem;
class UItemWidget;
class UButton;
class UNamedSlot;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnItemClickerClickedEvent, UItemClicker*, ClickedItemClicker );

/**
 * 
 */
UCLASS()
class E2EE_API UItemClicker : public UUserWidget
{
	GENERATED_BODY()

public:

	UItemClicker( const FObjectInitializer& ObjectInitializer );

protected:

	virtual void NativeOnInitialized() override;

public:

	UFUNCTION( BlueprintCallable )
	AItem* GetItem();

	UFUNCTION( BlueprintCallable )
	void SetItem( AItem* ItemToSet );

protected:

	UPROPERTY( meta = ( BindWidget ) )
	UButton* Button_Clicker;

	UPROPERTY( meta = ( BindWidget ) )
	UNamedSlot* NamedSlot_ItemWidgetSlot;

	UPROPERTY( BlueprintReadWrite )
	AItem* Item;

public:

	UPROPERTY( BlueprintAssignable )
	FOnItemClickerClickedEvent OnClicked;

protected:

	UFUNCTION()
	void HandleOnButtonClicked();
	
};
