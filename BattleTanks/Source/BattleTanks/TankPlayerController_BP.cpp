// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController_BP.h"

ATank * ATankPlayerController_BP::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}