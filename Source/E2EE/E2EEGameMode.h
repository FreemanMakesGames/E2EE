// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "E2EEGameMode.generated.h"

UCLASS( minimalapi )
class AE2EEGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	AE2EEGameMode();

protected:

	virtual void BeginPlay() override;

public:

};
