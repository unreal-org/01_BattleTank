// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//class UTankBarrel; // forward declaration
//class UTankAimingComponent;
//class UTankTurret;
//class AProjectile;
//class UTankMovementComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;

	// UPROPERTY(BlueprintReadOnly)
	// UTankAimingComponent* TankAimingComponent = nullptr;

	// UPROPERTY(BlueprintReadOnly)
	// UTankMovementComponent* TankMovementComponent = nullptr;

private:	
	// Sets default values for this pawn's properties
	ATank();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth = StartingHealth;
	
	// Called every frame
	// virtual void Tick(float DeltaTime) override; // not needed

	// Called to bind functionality to input
	// virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// move to aiming component
	// UPROPERTY(EditDefaultsOnly, Category = "Firing")
	// float LaunchSpeed = 1500;        // 1000 m/s default - find sensible value

	// UPROPERTY(EditDefaultsOnly, Category = "Setup")
	// TSubclassOf<AProjectile> ProjectileBlueprint;      // https://docs.unrealengine.com/en-US/Programming/UnrealArchitecture/TSubclassOf/index.html

	//UTankBarrel* Barrel = nullptr;

public:
	// called by engine when damage is dealt to actor by projectile's onhit applyradialdamage
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	// returns current health as a percentage of starting health
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;

	//void AimAt(FVector HitLocation);
	//UTankAimingComponent* GetTankAimingComponent() { return TankAimingComponent; }
	
	// UFUNCTION(BluePrintCallable)
	// void Fire();

	// UFUNCTION(BlueprintCallable, Category = "Setup")    // makes function callable from blueprint
	// void SetBarrelReference(UTankBarrel* BarrelToSet);

	// UFUNCTION(BlueprintCallable, Category = "Setup")    // makes function callable from blueprint
	// void SetTurretReference(UTankTurret* TurretToSet);

	// UPROPERTY(EditDefaultsOnly, Category = "Firing")
	// float ReloadTimeInSeconds = 3;

	// float LastFireTime = 0;     // use high precision timer for things like this
};
