#pragma once

#include "CoreMinimal.h"
#include "InventoryMenu.h"
#include "PlayerInventoryMenu.generated.h"

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
	
	virtual void ToggleInput( bool Enabled ) override;

};
