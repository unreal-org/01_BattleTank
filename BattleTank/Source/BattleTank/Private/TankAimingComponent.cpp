// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankBarrel.h"
//#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/GameplayStaticsTypes.h"
#include "Components/SceneComponent.h"
#include "Math/Rotator.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;    // should this tick?

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	// FString ThisTankName = GetOwner()->GetName();
	// FString BarrelLocation = Barrel->GetComponentLocation().ToString();
	// UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s."), *ThisTankName, *HitLocation.ToString(), *BarrelLocation);

	if (!Barrel) { return; }

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
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
		FString ThisTankName = GetOwner()->GetName();
		MoveBarrelTowards(AimDirection);
		UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s."),*ThisTankName, *AimDirection.ToString());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Aim Solution."));
	}
	
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// work out difference between current barrel rotation and aimdirection
	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotation;
	UE_LOG(LogTemp, Warning, TEXT("Aim Rotation is: %s."), *AimAsRotator.ToString());
	
	Barrel->Elevate(DeltaRotator.Pitch);
}
