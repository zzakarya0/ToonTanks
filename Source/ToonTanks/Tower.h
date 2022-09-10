// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

	virtual void HandleDestruction() override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Fire Components")
	float FireRange = 500.f;
	UPROPERTY(EditAnywhere, Category = "Fire Components")
	float FireRate = 2.5f;

	class ATank* PlayerTank;
	FTimerHandle FireTimerHandle;
	void CheckFireCondition();
	bool IsInFireRange();
};
