// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
//#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/GameplayStaticsTypes.h"
#include "Components/SceneComponent.h"
#include "Math/Rotator.h"
#include "Engine/World.h"
#include "Projectile.h"
#include "Math/Vector.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;    // should this tick? initially not necessary, but now it is

	// ...
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}
	

// void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
// {
// 	Barrel = BarrelToSet;
// }

// void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
// {
// 	Barrel = BarrelToSet;
// }

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// so that first fire is after inital reload
	LastFireTime = GetWorld()->GetTimeSeconds();
	
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	return !Barrel->GetForwardVector().Equals(AimDirection, 0.01);  // false if vectors equal
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// for reticle color mapping
	if (Ammo <= 0)
	{
		FiringStatus = EFiringStatus::OutOfAmmo;
	}
	else if ((GetWorld()->GetTimeSeconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringStatus = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringStatus = EFiringStatus::Aiming;
	}
	else
	{
		FiringStatus = EFiringStatus::Locked;
	}
	
}

void UTankAimingComponent::AimAt(FVector HitLocation)//, float LaunchSpeed)
{
	// FString ThisTankName = GetOwner()->GetName();
	// FString BarrelLocation = Barrel->GetComponentLocation().ToString();
	// UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s."), *ThisTankName, *HitLocation.ToString(), *BarrelLocation);

	if (!ensure(Barrel)) { return; }

	FVector OutLaunchVelocity(0);    // construct with 0
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
			this,
			OutLaunchVelocity,
			StartLocation,
			HitLocation,
			LaunchSpeed,
			false,  // default
			0,  // default
			0,  // default
			ESuggestProjVelocityTraceOption::DoNotTrace  // must be present - presents bug "no solution found"
		);

	// calculate launch vector
	if(bHaveAimSolution)
	{	
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		//FString ThisTankName = GetOwner()->GetName();
		//UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s."),*ThisTankName, *AimDirection.ToString());
	}
	// else
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("No Aim Solution."));
	// }
	
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel) || !ensure(Turret)) { return; }

	// work out difference between current barrel rotation and aimdirection
	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator TurretRotation = Turret->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotatorP = AimAsRotator - BarrelRotation;
	FRotator DeltaRotatorY = AimAsRotator - TurretRotation;
	//UE_LOG(LogTemp, Warning, TEXT("Aim Rotation is: %s."), *AimAsRotator.ToString());
	
	Barrel->Elevate(DeltaRotatorP.Pitch);
	if (FMath::Abs(DeltaRotatorY.Yaw) < 180)  // always yaw shortest way
	{
		Turret->Rotate(DeltaRotatorY.Yaw);
	}
	else
	{
		Turret->Rotate(-DeltaRotatorY.Yaw);
	}
	
}

void UTankAimingComponent::Fire()
{
	//UE_LOG(LogTemp, Warning, TEXT("Fire pressed."));
	//bool isReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTimeInSeconds;   // time in doubles

	//if (ensure(TankAimingComponent)) { Barrel = TankAimingComponent->GetBarrel(); }
	//if (!ensure(Barrel && ProjectileBlueprint)) { return; }

	//if (isReloaded) { 
	if (FiringStatus == EFiringStatus::Aiming || FiringStatus == EFiringStatus::Locked) {
		if (!ensure(Barrel && ProjectileBlueprint)) { return; }

		// spawn projectile at barrel firing socket
		FVector SpawnLocation = Barrel->GetSocketLocation(FName("Projectile"));
		FRotator SpawnRotation = Barrel->GetSocketRotation(FName("Projectile"));
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, SpawnLocation, SpawnRotation);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
		Ammo--;
	}
}

EFiringStatus UTankAimingComponent::GetFiringStatus() const
{
	return FiringStatus;
}


int UTankAimingComponent::GetAmmo() const
{
	return Ammo;
}