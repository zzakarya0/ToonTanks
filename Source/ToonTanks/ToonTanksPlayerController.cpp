// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksPlayerController.h"


void AToonTanksPlayerController::BeginPlay() {
	Super::BeginPlay();

	UpdateScoreHUD();
}

void AToonTanksPlayerController::SetPlayerEnabledState(bool bPlayerEnabled) {

	if (!bPlayerEnabled) GetPawn()->DisableInput(this);
	else GetPawn()->EnableInput(this);

	bShowMouseCursor = bPlayerEnabled;
}


void AToonTanksPlayerController::UpdateScore(AActor* DeadActor) {
	if (DeadActor->ActorHasTag(TEXT("Normal Enemy"))) CurrentScore += 10;

	// other enemy types have different score

	UpdateScoreHUD();
}