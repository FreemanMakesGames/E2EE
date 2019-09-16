#pragma once

#include "CoreMinimal.h"
#include "InventoryMenu.h"
#include "PlayerInventoryMenu.generated.h"

class ABasicPlayerController;
class UItemClicker;

class UButton;

/**
 * 
 */
UCLASS()
class E2EE_API UPlayerInventoryMenu : public UInventoryMenu
{
	GENERATED_BODY()

protected:

	virtual void NativeOnInitialized() override;

protected:

	UPROPERTY( meta = (BindWidget) )
	UItemMenu* ItemMenu;

	UPROPERTY( meta = ( BindWidget ) )
	UButton* Button_Close;

public:

	virtual void HideInventory() override;

protected:

	virtual void HandleOnItemClickerClicked( UItemClicker* ClickedItemClicker ) override;

#pragma region Item Menu event handlers
	UFUNCTION()
	void HandleOnItemMenuButtonDestroyClicked( UItemInfo* TargetItem );

	UFUNCTION()
	void HandleOnItemMenuButtonDropClicked( UItemInfo* TargetItem );

	UFUNCTION()
	void HandleOnItemMenuButtonDuplicateClicked( UItemInfo* TargetItem );

	UFUNCTION()
	void HandleOnItemMenuButtonOpenClicked( UItemInfo* TargetItem );

	UFUNCTION()
	void HandleOnItemMenuButtonReadClicked( UItemInfo* TargetItem );

	UFUNCTION()
	void HandleOnItemMenuButtonForCombinationClicked( UItemInfo* TargetItem );
#pragma endregion

	UFUNCTION()
	void HandleOnButtonCloseClicked();

protected:

	virtual void ToggleInput( bool Enabled ) override;

protected:

	ABasicPlayerController* PlayerController;

	bool bIsCombining;

	UItemInfo* FirstItemForCombination;

};
