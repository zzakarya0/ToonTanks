// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

class USpringArmComponent;
class UCameraComponent;

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
	
public:
	ATank();

	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;


private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* springArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* cameraComponent;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MovementSpeed;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnRate;
	
	void Move(float scale);
	void Turn(float scale);
	APlayerController* PlayerController;
};
