// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	if (!BarrelToSet) { return; }
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret * TurretToSet)
{
	if (!TurretToSet) { return; }
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	// Protect against nullptr in barrel
	if (!Barrel) { return; }

	// Setup variables for SuggestProjectileVelocity
	FVector out_LaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	FCollisionResponseParams CollisionResponseParams; // Not using this currently
	TArray<AActor*> IgnoreActors; // Not using this currently

	// Find out if we have a proper aim that is hitting something
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		out_LaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0.0f,
		0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if(bHaveAimSolution)
	{
		// Find an aim solution
		auto AimDirection = out_LaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}

}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	auto AimAsRotator = AimDirection.Rotation();

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto BarrelDeltaRotator = AimAsRotator - BarrelRotator;
	Barrel->Elevate(BarrelDeltaRotator.Pitch);

	auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto TurretDeltaRotator = AimAsRotator - TurretRotator;
	Turret->Rotate(TurretDeltaRotator.Yaw);

	// TODO figure out why AI turret isn't turning around properly
}

