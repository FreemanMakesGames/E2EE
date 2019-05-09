#pragma once

#include "ItemUsage.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemMenu.generated.h"

class UVerticalBox;
class UButton;
class AItem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnButtonDestroyClicked, AItem*, TargetItem );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnButtonDropClicked, AItem*, TargetItem );

/**
 * 
 */
UCLASS()
class E2EE_API UItemMenu : public UUserWidget
{
	GENERATED_BODY()

public:

	UItemMenu( const FObjectInitializer& ObjectInitializer );

	virtual void NativeOnInitialized() override;

public:

	UPROPERTY( BlueprintAssignable )
	FOnButtonDestroyClicked OnButtonDestroyClicked;

	UPROPERTY( BlueprintAssignable )
	FOnButtonDropClicked OnButtonDropClicked;

protected:

	UPROPERTY( meta = ( BindWidget ) )
	UVerticalBox* VerticalBox_Buttons;

	UPROPERTY( meta = ( BindWidget ) )
	UButton* Button_Destroy;

	UPROPERTY( meta = ( BindWidget ) )
	UButton* Button_Drop;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	TMap<EItemUsage, UButton*> ItemUsageToButton;

	UPROPERTY( VisibleAnywhere )
	AItem* CurrentItem;

public:

	UFUNCTION()
	void Display( AItem* Item );

protected:

	UFUNCTION()
	void HandleOnButtonDestroyClicked();

	UFUNCTION()
	void HandleOnButtonDropClicked();
	
};
