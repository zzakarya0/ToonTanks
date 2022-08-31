// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"


void ATower::BeginPlay() {
	Super::BeginPlay();

	PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (IsInFireRange()) RotateTurret(PlayerTank->GetActorLocation(), DeltaTime);
}

void ATower::CheckFireCondition() {
	
	if (IsInFireRange()) Fire();
}

bool ATower::IsInFireRange() {
	if (!PlayerTank) return false;

	return (FVector::Distance(GetActorLocation(), PlayerTank->GetActorLocation()) <= FireRange);
}
