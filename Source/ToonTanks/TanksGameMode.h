// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATanksGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	void ActorDied(AActor* DeadActor);

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bPlayerWon);

private:
	class ATank* PlayerTank;

	class AToonTanksPlayerController* TankPlayerController;

	float TimerRate = 3.f;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FTimerHandle PlayerEnableTimerHandle;

	void HandleGameStart();

	int32 EnemiesCount;

	int32 GetEnemiesCount();
};
