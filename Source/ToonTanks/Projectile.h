// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Combat Components")
	float Damage = 20.f;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditAnywhere, Category = "Combat Components")
	class UProjectileMovementComponent* ProjectileMovementComp;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	class UParticleSystem* HitParticles;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	class UParticleSystemComponent* TrailEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	class USoundBase* LaunchSound;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category = "Effects")
	TSubclassOf<class UCameraShakeBase> HitCameraShakeClass;
};
