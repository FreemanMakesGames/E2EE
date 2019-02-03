// Fill out your copyright notice in the Description page of Project Settings.

#include "E2EEGameStateBase.h"

int AE2EEGameStateBase::GetCurrentKeyPairID()
{
	return CurrentKeyPairID;
}

void AE2EEGameStateBase::IncrementCurrentKeyPairID()
{
	CurrentKeyPairID++;
}
