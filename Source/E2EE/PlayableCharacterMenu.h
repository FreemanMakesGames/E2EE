#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayableCharacterMenu.generated.h"

class ABasicCharacter;

class UButton;

/**
 * 
 */
UCLASS()
class E2EE_API UPlayableCharacterMenu : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeOnInitialized() override;

public:

	void SetOwnerCharacter( ABasicCharacter* InOwnerCharacter );

protected:

	UPROPERTY( meta = ( BindWidget ) )
	UButton* Button_ViewInventory;

	UPROPERTY( meta = ( BindWidget ) )
	UButton* Button_PickUpItems;

	UPROPERTY( meta = ( BindWidget ) )
	UButton* Button_SendItems;

	UPROPERTY( meta = ( BindWidget ) )
	UButton* Button_Back;

public:

	UFUNCTION( BlueprintImplementableEvent )
	void Show();

	UFUNCTION( BlueprintImplementableEvent )
	void Hide();

protected:

	UFUNCTION()
	void HandleOnButtonViewInventoryClicked();

	UFUNCTION()
	void HandleOnButtonPickUpItemsClicked();

	UFUNCTION()
	void HandleOnButtonSendItemsClicked();

	UFUNCTION()
	void HandleOnButtonBackClicked();

protected:

	ABasicCharacter* OwnerCharacter;
	
};
