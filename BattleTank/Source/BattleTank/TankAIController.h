// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Tank.h"
//#include "TankAimingComponent.h"

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	// ATank* GetControlledTank() const;
	// ATank* GetPlayerTank() const;
	virtual void BeginPlay() override;      // override AActor's virtual BeginPlay

	virtual void Tick(float DeltaTime) override;

	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
	void OnPossessedTankDeath();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 1000;
};
