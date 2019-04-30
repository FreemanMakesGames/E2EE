// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemClicker.h"

#include "Components/Button.h"

UItemClicker::UItemClicker( const FObjectInitializer& ObjectInitializer ) : Super( ObjectInitializer )
{

}

void UItemClicker::NativeOnInitialized()
{
	Button_Clicker->OnClicked.AddDynamic( this, &UItemClicker::HandleOnButtonClicked );
}

void UItemClicker::HandleOnButtonClicked()
{
	UE_LOG( LogTemp, Warning, TEXT( "CLICKED" ) );
}
