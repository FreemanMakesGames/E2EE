// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HomeMenu.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class E2EE_API UHomeMenu : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY( meta = ( BindWidget ) )
	UButton* Button_LocalGame;

	UPROPERTY( meta = ( BindWidget ) )
	UButton* Button_OnlineGame;

	UPROPERTY( meta = ( BindWidget ) )
	UButton* Button_Exit;
	
};
