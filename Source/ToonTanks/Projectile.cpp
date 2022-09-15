// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	SetRootComponent(ProjectileMesh);

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement Compoenent"));
	ProjectileMovementComp->InitialSpeed = 150.f;
	ProjectileMovementComp->MaxSpeed = 300.f;

	TrailEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Taril Effect Component"));
	TrailEffect->SetupAttachment(ProjectileMesh);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay() {
	Super::BeginPlay();

	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	//UE_LOG(LogTemp, Display, TEXT("HIT COMP: %s, OTHER ACTOR: %s, OTHER COMP: %s, NORMAL IMPULSE: %s"), *HitComp->GetName(), *OtherActor->GetName(), *OtherComp->GetName(), *NormalImpulse.ToCompactString());

	if (OtherActor && OtherActor != this && OtherActor != GetOwner())
		UGameplayStatics::ApplyDamage(OtherActor, Damage, GetOwner()->GetInstigatorController(), this, UDamageType::StaticClass());
	
	if (HitParticles) UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation());
	Destroy();
}

