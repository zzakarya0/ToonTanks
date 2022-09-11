// Fill out your copyright notice in the Description page of Project Settings.


#include "TanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

void ATanksGameMode::BeginPlay() {
	Super::BeginPlay();

	HandleGameStart();
}

void ATanksGameMode::ActorDied(AActor* DeadActor) {
	//UE_LOG(LogTemp, Warning, TEXT("Actor Died!!"));

	ABasePawn* Pawn = Cast<ABasePawn>(DeadActor);
	if (Pawn) Pawn->HandleDestruction();
	if (Cast<ATank>(Pawn)) TankPlayerController->SetPlayerEnabledState(false);
}

void ATanksGameMode::HandleGameStart() {
	PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	TankPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	if (TankPlayerController) {
		StartGame();
		TankPlayerController->SetPlayerEnabledState(false);

		FTimerDelegate PlayerStartDelegate = FTimerDelegate::CreateUObject(TankPlayerController, &AToonTanksPlayerController::SetPlayerEnabledState, true);
		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerStartDelegate, TimerRate, false);
	}
}

