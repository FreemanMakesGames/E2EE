#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterMenu.generated.h"

class ABasicCharacter;

class UButton;

/**
 * 
 */
UCLASS()
class E2EE_API UCharacterMenu : public UUserWidget
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

protected:

	UFUNCTION( BlueprintCallable )
	void HandleOnButtonViewInventoryClicked();

	UFUNCTION( BlueprintCallable )
	void HandleOnButtonPickUpItemsClicked();

	UFUNCTION( BlueprintCallable )
	void HandleOnButtonSendItemsClicked();

	UFUNCTION( BlueprintCallable )
	void HandleOnButtonBackClicked();

protected:

	ABasicCharacter* OwnerCharacter;
	
};
