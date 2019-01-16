// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Item.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

UCLASS( ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent ) )
class E2EE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UInventoryComponent();

protected:

	virtual void BeginPlay() override;

	AActor* MyOwner;

	TArray<FItem> Items;

public:

	TArray<FItem> GetItems();

	void AddItem( FItem NewItem );

};
