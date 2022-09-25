// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

class UCapsuleComponent;

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateHealthWidget() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void RotateTurret(FVector TargetPoint, float DeltaTime);
	
	void Fire();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void HandleDestruction();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* capsuleCollider;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* baseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* turretMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent* projectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurretRotationSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health Component", meta = (AllowPrivateAccess = "true"))
	class UHealthComponent* HealthComp;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	class UParticleSystem* DeathEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	class USoundBase* DeathSound;

	UPROPERTY(EditAnywhere, Category = "Effects")
	TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass;
};
