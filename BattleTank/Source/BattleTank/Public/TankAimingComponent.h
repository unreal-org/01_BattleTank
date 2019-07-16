// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for aiming state
UENUM()
enum class EFiringStatus : uint8
{
	Reloading,
	Aiming,
	Locked
};

// Forward Declaration
class UTankBarrel;
class UTankTurret;
class AProjectile;

// Holds Barrel's properties
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	// void SetBarrelReference(UTankBarrel* BarrelToSet);   // set barrel position
	// void SetTurretReference(UTankTurret* TurretToSet);   // set barrel position
	
	// set turret & barrel reference
	UFUNCTION(BluePrintCallable, Category = "Setup")      
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	
protected:
	// Called when the game starts
	// virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "Status")    // access from tank aiming component bp - protect
	EFiringStatus FiringStatus = EFiringStatus::Aiming;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AimAt(FVector HitLocation);//, float LaunchSpeed);

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3;

	float LastFireTime = 0;     // use high precision timer for things like this

	UFUNCTION(BluePrintCallable)
	void Fire();

private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	void MoveBarrelTowards(FVector AimDirection);

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 1500;        // 1000 m/s default - find sensible value

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;      // https://docs.unrealengine.com/en-US/Programming/UnrealArchitecture/TSubclassOf/index.html

};
