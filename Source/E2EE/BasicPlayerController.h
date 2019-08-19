#pragma once

#include "Team.h"

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasicPlayerController.generated.h"

class ABasicCharacter;
class UInventoryMenu;
class UInventory;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnTeamSelectionResultReceived, bool, bSuccessful );

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

public:

	UFUNCTION( BlueprintCallable )
	ABasicCharacter* GetActiveCharacter();

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
	void ClientReceiveCharacterInteractionResult( bool bSuccessful, ABasicCharacter* TargetCharacter );

	UFUNCTION( BlueprintCallable )
	void ShowInventoryMenu();

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable )
	void DisplayNotification( const FString& NotificationString );

};
