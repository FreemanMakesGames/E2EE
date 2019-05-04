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

	UPROPERTY( BlueprintReadWrite )
	AItem* Item;

protected:

	UPROPERTY( meta = ( BindWidget ) )
	UButton* Button_Clicker;

	UPROPERTY( meta = ( BindWidget ) )
	UNamedSlot* NamedSlot_ItemWidgetSlot;

public:

	UPROPERTY( BlueprintAssignable )
	FOnItemClickerClickedEvent OnClicked;

	void InsertItemWidget( UItemWidget* ItemWidget );

protected:

	UFUNCTION()
	void HandleOnButtonClicked();
	
};
