// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Public\Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
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

private:
	ATank * PossessedTank;
};
