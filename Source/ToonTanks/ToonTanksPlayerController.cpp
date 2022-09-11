// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksPlayerController.h"

void AToonTanksPlayerController::SetPlayerEnabledState(bool bPlayerEnabled) {

	if (!bPlayerEnabled) GetPawn()->DisableInput(this);
	else GetPawn()->EnableInput(this);

	bShowMouseCursor = bPlayerEnabled;
}
