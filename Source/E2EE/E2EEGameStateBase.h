// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "E2EEGameStateBase.generated.h"

UCLASS()
class E2EE_API AE2EEGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:

	UFUNCTION( BlueprintCallable )
	void IncrementUsableKeyPairID();

protected:

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	int NextUsableKeyPairID;
	
};
