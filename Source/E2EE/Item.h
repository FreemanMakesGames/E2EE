// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Command.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class UCommand;

UCLASS( BlueprintType )
class E2EE_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	

	AItem();

protected:

	virtual void BeginPlay() override;

	TArray<UCommand*> Commands;

	UCommand* ActiveCommand;

public:	

	virtual void Tick(float DeltaTime) override;

};
