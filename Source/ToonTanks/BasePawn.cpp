// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	capsuleCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	SetRootComponent(capsuleCollider);

	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	baseMesh->SetupAttachment(capsuleCollider);

	turretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	turretMesh->SetupAttachment(baseMesh);

	projectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn"));
	projectileSpawnPoint->SetupAttachment(turretMesh);
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasePawn::RotateTurret(FVector TargetPoint, float DeltaTime) {
	FVector ToTarget = TargetPoint - turretMesh->GetComponentLocation();
	FRotator LookDirection = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);

	turretMesh->SetWorldRotation(FMath::RInterpConstantTo(turretMesh->GetComponentRotation(), LookDirection, DeltaTime, TurretRotationSpeed));
}

void ABasePawn::Fire() {
	DrawDebugSphere(GetWorld(), projectileSpawnPoint->GetComponentLocation(), 15.f, 15, FColor::Blue, false, 3.f);
}