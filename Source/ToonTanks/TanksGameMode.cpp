// Fill out your copyright notice in the Description page of Project Settings.


#include "TanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"

void ATanksGameMode::BeginPlay() {
	Super::BeginPlay();

	PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void ATanksGameMode::ActorDied(AActor* DeadActor) {
	UE_LOG(LogTemp, Warning, TEXT("Actor Died!!"));

	ABasePawn* Pawn = Cast<ABasePawn>(DeadActor);
	if (Pawn) Pawn->HandleDestruction();
}

