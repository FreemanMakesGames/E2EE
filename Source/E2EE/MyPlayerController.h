// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class AE2EECharacter;

UCLASS()
class E2EE_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	AMyPlayerController();

protected:

	virtual void SetupInputComponent() override;

	virtual void BeginPlay() override;

protected:

	void ZoomIn();

	void ZoomOut();

	UFUNCTION( BlueprintImplementableEvent )
	void ToggleInventory();

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	AE2EECharacter* ActiveCharacter;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	TSubclassOf<class UUserWidget> InventoryWidgetClass;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	UUserWidget* InventoryWidget;

	UPROPERTY()
	AActor* Camera_Overview;

public:

	AE2EECharacter* GetActiveCharacter();

	void SetActiveCharacter( AE2EECharacter* Character );
	
};
