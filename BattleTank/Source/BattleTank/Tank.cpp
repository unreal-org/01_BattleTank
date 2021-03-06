// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
//#include "TankAimingComponent.h"
// #include "UObject/UObjectGlobals.h"
// #include "Engine/World.h"
// #include "Components/SceneComponent.h"
// #include "Math/Rotator.h"
// #include "TankBarrel.h"
// #include "Projectile.h"
// //#include "TankMovementComponent.h"
// #include "GameFramework/Actor.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/Actor.h"
#include "GenericPlatform/GenericPlatformMath.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	//TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp<float>(DamagePoints, 0, CurrentHealth);

	CurrentHealth = CurrentHealth - DamageToApply;
	if (CurrentHealth <= 0)
	{
			OnDeath.Broadcast();   // general broadcast of death - not specifically to anything
	}

	return DamageToApply;
}

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth;    // float casting
}


// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();  // needed for blueprint beginplay

	//TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
	CurrentHealth = StartingHealth;
}

// Called every frame
// void ATank::Tick(float DeltaTime)
// {
// 	Super::Tick(DeltaTime);

// }

// Called to bind functionality to input
// void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
// {
// 	Super::SetupPlayerInputComponent(PlayerInputComponent);
// }

// void ATank::AimAt(FVector HitLocation)
// {
// 	if (!ensure(TankAimingComponent)) { return; }
// 	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
// }

// void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
// {
// 	//TankAimingComponent->SetBarrelReference(BarrelToSet);
// 	Barrel = BarrelToSet;
// }

// void ATank::SetTurretReference(UTankTurret* TurretToSet)
// {
// 	TankAimingComponent->SetTurretReference(TurretToSet);
// }

// void ATank::Fire()
// {
// 	//UE_LOG(LogTemp, Warning, TEXT("Fire pressed."));
// 	bool isReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTimeInSeconds;   // time in doubles
// 	//if (ensure(TankAimingComponent)) { Barrel = TankAimingComponent->GetBarrel(); }
// 	if (!ensure(Barrel)) { return; }

// 	if (isReloaded) { 
// 		// spawn projectile at barrel firing socket
// 		FVector SpawnLocation = Barrel->GetSocketLocation(FName("Projectile"));
// 		FRotator SpawnRotation = Barrel->GetSocketRotation(FName("Projectile"));
// 		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, SpawnLocation, SpawnRotation);

// 		Projectile->LaunchProjectile(LaunchSpeed);
// 		LastFireTime = GetWorld()->GetTimeSeconds();
// 	}
// }

