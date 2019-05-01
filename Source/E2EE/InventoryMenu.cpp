// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryMenu.h"

#include "ItemClicker.h"

#include "Components/WrapBox.h"

void UInventoryMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UE_LOG( LogTemp, Warning, TEXT( "UInventoryMenu.NativeOnInitialized" ) );

	for ( int i = 0; i < 18; i++ )
	{
		UItemClicker* NewItemClicker = CreateWidget<UItemClicker>( this, ItemClickerClass );

		WrapBox_ItemClickers->AddChildWrapBox( NewItemClicker );
	}
}
