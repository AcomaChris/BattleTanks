// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "CoreMinimal.h"
#include "TankAIController.generated.h"

// Forward declarations
class ATank;

/**
 *
 */
UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay();

	virtual void Tick(float DeltaTime) override;

private:

	ATank * GetAIControlledTank() const;

	ATank * PossessedAITank;

	ATank * GetPlayerTank() const;

};
