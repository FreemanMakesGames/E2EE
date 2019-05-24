#pragma once

#include "ItemUsage.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemMenu.generated.h"

class UVerticalBox;
class UButton;
class UItemInfo;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnButtonDestroyClicked, UItemInfo*, TargetItem );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnButtonDropClicked, UItemInfo*, TargetItem );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnButtonDuplicateClicked, UItemInfo*, TargetItem );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnButtonOpenClicked, UItemInfo*, TargetItem );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnButtonReadClicked, UItemInfo*, TargetItem );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnButtonForCombinationClicked, UItemInfo*, TargetItem );

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

#pragma region Button events
public:

	UPROPERTY( BlueprintAssignable )
	FOnButtonDestroyClicked OnButtonDestroyClicked;

	UPROPERTY( BlueprintAssignable )
	FOnButtonDropClicked OnButtonDropClicked;

	UPROPERTY( BlueprintAssignable )
	FOnButtonDuplicateClicked OnButtonDuplicateClicked;

	UPROPERTY( BlueprintAssignable )
	FOnButtonOpenClicked OnButtonOpenClicked;

	UPROPERTY( BlueprintAssignable )
	FOnButtonReadClicked OnButtonReadClicked;

	UPROPERTY( BlueprintAssignable )
	FOnButtonForCombinationClicked OnButtonForCombinationClicked;
#pragma endregion

protected:

	UPROPERTY( meta = ( BindWidget ) )
	UVerticalBox* VerticalBox_Buttons;

#pragma region UButtons
	UPROPERTY( meta = ( BindWidget ) )
	UButton* Button_Destroy;

	UPROPERTY( meta = ( BindWidget ) )
	UButton* Button_Drop;

	UPROPERTY( meta = ( BindWidget ) )
	UButton* Button_Duplicate;

	UPROPERTY( meta = ( BindWidget ) )
	UButton* Button_Lock;

	UPROPERTY( meta = ( BindWidget ) )
	UButton* Button_Unlock;

	UPROPERTY( meta = ( BindWidget ) )
	UButton* Button_Open;

	UPROPERTY( meta = ( BindWidget ) )
	UButton* Button_Read;

	UPROPERTY( meta = ( BindWidget ) )
	UButton* Button_Contain;
#pragma endregion

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	TMap<EItemUsage, UButton*> ItemUsageToButton;

	UPROPERTY( VisibleAnywhere )
	UItemInfo* CurrentItem;

public:

	UFUNCTION()
	void Display( UItemInfo* Item );

protected:

#pragma region Button event handlers
	UFUNCTION()
	void HandleOnButtonDestroyClicked();

	UFUNCTION()
	void HandleOnButtonDropClicked();

	UFUNCTION()
	void HandleOnButtonDuplicateClicked();

	UFUNCTION()
	void HandleOnButtonOpenClicked();

	UFUNCTION()
	void HandleOnButtonReadClicked();

	UFUNCTION()
	void HandleOnButtonForCombinationClicked();
#pragma endregion
	
};
