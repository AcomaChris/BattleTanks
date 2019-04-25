// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Public\Tank.h"
#include "CoreMinimal.h"
#include "GameFramework\PlayerController.h"
#include "Engine\Classes\Engine\World.h"
#include "TankPlayerController_BP.generated.h" // Must be the last include

/**
 *
 */
UCLASS()
class BATTLETANKS_API ATankPlayerController_BP : public APlayerController
{
	GENERATED_BODY()

public:
	ATank * GetControlledTank() const;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	ATank * PossessedTank = nullptr;

	// Start the tank moving the barrel so that a shot would hit where
	// the crosshair intersects the world
	void AimTowardsCrosshair();

	// Function for getting the hit location from the screen space crosshair dot
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	// Crosshair setup values
	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5f;
	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 1.0f / 3.0f;

	// Line trace variables; set to 10km by default
	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.0f;

	// Line trace functions
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	bool GetLookDirectionHitLocation(FVector LookDirection, FVector& HitLocation) const;
};