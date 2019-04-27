// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0f, 1.0f);

	// Find the elevation change we want to make
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;

	// Set the barrel elevation to the new pitch
	float Rotation = RelativeRotation.Yaw + RotationChange;

	// Sets the rotation of the turret
	SetRelativeRotation(FRotator(0.0f, Rotation, 0.0f));

}
