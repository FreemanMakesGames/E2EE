#pragma once

#include "Team.h"

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasicPlayerController.generated.h"

class ABasicCharacter;
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

	ABasicCharacter* GetActiveCharacter();

	void SetActiveCharacter( ABasicCharacter* Character );

protected:

	UPROPERTY( EditDefaultsOnly )
	TSubclassOf<UInventoryMenu> InventoryMenuClass;

	UPROPERTY()
	UInventoryMenu* InventoryMenu;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	ABasicCharacter* ActiveCharacter;

public:

	UFUNCTION( Server, Reliable, WithValidation, BlueprintCallable )
	void SubmitTeamSelectionRequest( ETeam Team );

	UFUNCTION( BlueprintCallable )
	void ShowInventoryMenu( UInventory* Inventory );

};
