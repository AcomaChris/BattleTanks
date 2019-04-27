// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	// Work out difference between current barrel rotation and aim direction
	// Move the barrel the right amount this frame, given the max elevation speed and frame time

	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0f, 1.0f);

	// Find the elevation change we want to make
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;

	// Set the barrel elevation to the new pitch
	float RawNewRotation = RelativeRotation.Yaw + RotationChange;

	// Sets the rotation of the turret
	SetRelativeRotation(FRotator(0.0f, RawNewRotation, 0.0f));

}
