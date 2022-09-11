// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
//#include "DrawDebugHelpers.h"


ATank::ATank() {
	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	springArm->SetupAttachment(RootComponent);

	cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Main Camera"));
	cameraComponent->SetupAttachment(springArm);
}

void ATank::BeginPlay() {
	Super::BeginPlay();

	PlayerController = Cast<APlayerController>(GetController());
}

void ATank::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (!PlayerController) return;
	
	FHitResult outHit;
	PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, outHit);
	//DrawDebugSphere(GetWorld(), outHit.ImpactPoint, 10, 10, FColor::Red, false);
	RotateTurret(outHit.ImpactPoint, DeltaTime);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &ATank::Fire);
}

void ATank::Move(float scale) {
	FVector DeltaLocation(0.f);
	DeltaLocation.X = scale * MovementSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);

	AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float scale) {
	FRotator DeltaRotation = FRotator::ZeroRotator;
	DeltaRotation.Yaw = scale * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);

	AddActorLocalRotation(DeltaRotation, true);
}

void ATank::HandleDestruction() {
	Super::HandleDestruction();

	//DisableInput(PlayerController);
	//PlayerController->bShowMouseCursor = false;
	SetActorHiddenInGame(true);
	//PrimaryActorTick.bCanEverTick = false;
	SetActorTickEnabled(false);
	
}