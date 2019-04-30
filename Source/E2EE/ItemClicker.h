// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemClicker.generated.h"

class AItem;
class UButton;

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

public:

	AItem* Item;

	FOnItemClickerClickedEvent OnClicked;

protected:

	virtual void NativeOnInitialized() override;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	UUserWidget* ItemWidget;

	UPROPERTY( meta = ( BindWidget ) )
	UButton* Button_Clicker;

	UFUNCTION()
	void HandleOnButtonClicked();
	
};
