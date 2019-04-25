// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Public\Tank.h"
#include "Engine\Classes\Engine\World.h"
#include "GameFramework/PlayerController.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

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
