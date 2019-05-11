// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Command.h"
#include "DestroyCommand.generated.h"

/**
 * 
 */
UCLASS()
class E2EE_API UDestroyCommand : public UCommand
{
	GENERATED_BODY()

public:

	UDestroyCommand();

	virtual void Execute() override;
	
};
