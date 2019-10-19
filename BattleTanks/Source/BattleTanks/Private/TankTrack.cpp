// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

// Sets the throttle for the attached track
void UTankTrack::SetThrottle(float Throttle)
{
	// TODO clamp actual throttle value so player cannot over-drive
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
