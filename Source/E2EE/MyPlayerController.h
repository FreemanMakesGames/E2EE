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

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	AE2EECharacter* ActiveCharacter;

	UPROPERTY()
	AActor* Camera_Overview;

public:

	AE2EECharacter* GetActiveCharacter();

	UFUNCTION( Server, Reliable, WithValidation )
	void ServerSetActiveCharacter( AE2EECharacter* CharacterToSet );
	
};
