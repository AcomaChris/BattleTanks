// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController_BP.h"

void ATankPlayerController_BP::BeginPlay()
{
	Super::BeginPlay();

	ATank * PossessedTank = GetControlledTank();

	if (!PossessedTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Found possessed tank: %s"), *(PossessedTank->GetName()));
	}

}

// Called every frame
void ATankPlayerController_BP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

ATank * ATankPlayerController_BP::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController_BP::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; // Out parameter

	if (GetSightRayHitLocation(HitLocation))
	{
		// Tell controlled tank to aim at point
		GetControlledTank()->AimAt(HitLocation);
	}

}

bool ATankPlayerController_BP::GetSightRayHitLocation(FVector& out_HitLocation) const
{
	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;

	// Gets the size of the screen viewport and finds the screen location we want to shoot at
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	// Deproject the screen position of the crosshair to a world direction
	FVector LookDirection = FVector(1.0f);
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line track along that LookDirection and see what we hit (up to a maximum range)
		GetLookDirectionHitLocation(LookDirection, out_HitLocation);

		return true;
	}

	return false;
}

bool ATankPlayerController_BP::GetLookDirection(FVector2D ScreenLocation, FVector& out_LookDirection) const
{
	// Variable required for function; gets discard
	FVector CameraWorldLocation = FVector(1.0f);

	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		out_LookDirection);
}

bool ATankPlayerController_BP::GetLookDirectionHitLocation(FVector LookDirection, FVector& out_HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility))// Line trace succeeds
	{
		out_HitLocation = HitResult.Location;
		return true;
	}

	out_HitLocation = FVector(0.0f);
	return false;
}