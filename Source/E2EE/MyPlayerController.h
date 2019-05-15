#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class AE2EECharacter;
class UInventoryMenu;
class UInventory;

UCLASS()
class E2EE_API ABasicPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	ABasicPlayerController();

protected:

	virtual void SetupInputComponent() override;

	virtual void BeginPlay() override;

public:

	AE2EECharacter* GetActiveCharacter();

	void SetActiveCharacter( AE2EECharacter* Character );

	UFUNCTION( BlueprintCallable )
	void ShowInventoryMenu( UInventory* Inventory );

protected:

	UPROPERTY( EditDefaultsOnly )
	TSubclassOf<UInventoryMenu> InventoryMenuClass;

	UPROPERTY()
	UInventoryMenu* InventoryMenu;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	AE2EECharacter* ActiveCharacter;

};
