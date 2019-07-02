// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel; // forward declaration
class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UTankAimingComponent* TankAimingComponent = nullptr;

private:	
	// Sets default values for this pawn's properties
	ATank();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	void AimAt(FVector HitLocation);
	//UTankAimingComponent* GetTankAimingComponent() { return TankAimingComponent; }

	UFUNCTION(BlueprintCallable, Category = "Setup")    // makes function callable from blueprint
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UPROPERTY(EditAnywhere, Category = "Firing")
	float LaunchSpeed = 100000;        // 1000 m/s default - find sensible value
};
