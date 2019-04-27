// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/Classes/GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "TankAimingComponent.generated.h"

// Forward Declaration
class UTankBarrel;
class UTankTurret;

// Holds barrel's properties and elevate methods
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTankAimingComponent();

	void SetBarrelReference(UTankBarrel * BarrelToSet);
	void SetTurretReference(UTankTurret * TurretToSet);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Aim at a place in world space
	void AimAt(FVector WorldSpaceAim, float LaunchSpeed);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	// Barrel and turret variables
	UTankBarrel * Barrel = nullptr;
	UTankTurret * Turret = nullptr;

	// Move the barrel to the correct location
	void MoveBarrelTowards(FVector AimDirection);

};
