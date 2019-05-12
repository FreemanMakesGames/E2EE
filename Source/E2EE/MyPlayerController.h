#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class AE2EECharacter;
class UInventoryMenu;
class UInventory;

UCLASS()
class E2EE_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	AMyPlayerController();

protected:

	virtual void SetupInputComponent() override;

	virtual void BeginPlay() override;

public:

	AE2EECharacter* GetActiveCharacter();

	void SetActiveCharacter( AE2EECharacter* Character );

	UFUNCTION( BlueprintCallable )
	void ShowInventoryMenu( UInventory* Inventory );

protected:

	void ZoomIn();

	void ZoomOut();

	UPROPERTY( EditDefaultsOnly )
	TSubclassOf<UInventoryMenu> InventoryMenuClass;

	UPROPERTY()
	UInventoryMenu* InventoryMenu;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	AE2EECharacter* ActiveCharacter;

	UPROPERTY()
	AActor* Camera_Overview;

};
