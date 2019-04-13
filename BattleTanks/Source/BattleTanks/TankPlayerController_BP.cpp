// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController_BP.h"

void ATankPlayerController_BP::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("PlayerController BeginPlay"));

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

ATank * ATankPlayerController_BP::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}