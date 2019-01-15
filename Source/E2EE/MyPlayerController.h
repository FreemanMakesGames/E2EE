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

protected:

	virtual void SetupInputComponent() override;

protected:

	AE2EECharacter* ActiveCharacter;

	void ZoomIn();

	void ZoomOut();

	void DisplayInventory();

public:

	void SetActiveCharacter( AE2EECharacter* Character );
	
};
