// Fill out your copyright notice in the Description page of Project Settings.


#include "TanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

void ATanksGameMode::BeginPlay() {
	Super::BeginPlay();

	HandleGameStart();
	EnemiesCount = GetEnemiesCount();
}

void ATanksGameMode::ActorDied(AActor* DeadActor) {
	ABasePawn* deadPawn = Cast<ABasePawn>(DeadActor);
	if (deadPawn) deadPawn->HandleDestruction();

	if (Cast<ATank>(deadPawn)) {
		TankPlayerController->SetPlayerEnabledState(false);
		GameOver(false);
	} 
	else if (Cast<ATower>(deadPawn)) {
		--EnemiesCount;
		TankPlayerController->UpdateScore(DeadActor);

		if (!EnemiesCount) GameOver(true);
	}
}

void ATanksGameMode::HandleGameStart() {
	PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	TankPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	if (TankPlayerController) {
		StartGame();
		TankPlayerController->SetPlayerEnabledState(false);

		FTimerDelegate PlayerStartDelegate = FTimerDelegate::CreateUObject(TankPlayerController, &AToonTanksPlayerController::SetPlayerEnabledState, true);
		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerStartDelegate, StartTimerRate, false);
	}
}

int32 ATanksGameMode::GetEnemiesCount() {
	TArray<AActor*> outEnemies;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), outEnemies);

	return outEnemies.Num();
}
