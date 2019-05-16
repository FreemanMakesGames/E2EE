#pragma once

#include "Team.h"

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasicPlayerController.generated.h"

class ABasicCharacter;
class UInventoryMenu;
class UInventory;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnTeamSelectionResultReceived, bool, bSuccessful );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnCharacterInteractionResultReceived, bool, bSuccessful );

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

	UPROPERTY( BlueprintAssignable )
	FOnTeamSelectionResultReceived OnTeamSelectionResultReceived;

	UPROPERTY( BlueprintAssignable )
	FOnCharacterInteractionResultReceived OnCharacterInteractionResultReceived;

public:

	ABasicCharacter* GetActiveCharacter();

	void SetActiveCharacter( ABasicCharacter* Character );

protected:

	UPROPERTY( EditDefaultsOnly )
	TSubclassOf<UInventoryMenu> InventoryMenuClass;

	UPROPERTY( BlueprintReadOnly )
	UInventoryMenu* InventoryMenu;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	ABasicCharacter* ActiveCharacter;

public:

	UFUNCTION( Server, Reliable, WithValidation, BlueprintCallable )
	void ServerSubmitTeamSelectionRequest( ETeam Team );

	UFUNCTION( Client, Reliable )
	void ClientReceiveTeamSelectionResult( bool bSuccessful );

	UFUNCTION( Server, Reliable, WithValidation, BlueprintCallable )
	void ServerSubmitCharacterInteractionRequest( ABasicCharacter* TargetCharacter );

	UFUNCTION( Client, Reliable )
	void ClientReceiveCharacterInteractionResult( bool bSuccessful );

	UFUNCTION( BlueprintCallable )
	void ShowInventoryMenu();

};
