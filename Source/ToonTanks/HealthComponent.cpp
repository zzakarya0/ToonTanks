// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "TanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "BasePawn.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UHealthComponent::BeginPlay() {
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeDamage);

	GameMode = Cast<ATanksGameMode>(UGameplayStatics::GetGameMode(this));
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser) {
	//UE_LOG(LogTemp, Display, TEXT("       HEALTH: %f"), CurrentHealth);
	if (Damage == 0) return;

	CurrentHealth -= Damage;
	UpdatePawnHealthWidget();

	if (GameMode && CurrentHealth <= 0.f) GameMode->ActorDied(DamagedActor);
}

void UHealthComponent::UpdatePawnHealthWidget() const {
	//GetHealthPercent();
	ABasePawn* owner = Cast<ABasePawn>(GetOwner());

	if (owner) owner->UpdateHealthWidget();
}

float UHealthComponent::GetHealthPercent() const { 
	UE_LOG(LogTemp, Warning, TEXT("CURRENT HEALTH: %d"), CurrentHealth);

	float f = CurrentHealth / 100.f;
	UE_LOG(LogTemp, Warning, TEXT("HEALTH PERCENT: %f"), f);

	return f;
}
