// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Engine/EngineTypes.h"
//#include "Public/CollisionQueryParams.h"
#include "GameFramework/Actor.h"
#include "TankAimingComponent.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    // ATank* ControlledTank = GetControlledTank();
    // if (!ControlledTank)
    // {
    //     UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank."));
    // }
    // else 
    // {
    //     UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing %s."), *ControlledTank->GetName());
    // }
    // UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play."));

    //UTankAimingComponent* AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
    UTankAimingComponent* AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if (ensure(AimingComponent))
    {
        FoundAimingComponent(AimingComponent);
    }
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    AimTowardCrosshair();
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
    Super::SetPawn(InPawn);
    if (InPawn)
    {
        ATank* PlayerTank = Cast<ATank>(InPawn);
        if (!ensure(PlayerTank)) { return; }

        // subscribe our local method and listen to the tank's death broadcast
        PlayerTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPlayerTankDeath);
    }
}

void ATankPlayerController::OnPlayerTankDeath()
{
    StartSpectatingOnly();
}

// ATank* ATankPlayerController::GetControlledTank() const    // take note of prefix "A"
// {
//     //return Cast<ATank>(GetPawn());
//     return GetPawn();
// }

void ATankPlayerController::AimTowardCrosshair()
{
    //if (!ensure(GetControlledTank())) { return; }
    if (!GetPawn()) { return; }   // if not possessing
    UTankAimingComponent* AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if (ensure(AimingComponent))
    {
    // float Time = GetWorld()->GetTimeSeconds();
    // UE_LOG(LogTemp, Warning, TEXT("%f: AimTowardCrosshair called."), Time);

        FVector HitLocation; // OUT parameter
        if (GetSightRayHitLocation(HitLocation))
        {
            //UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
            AimingComponent->AimAt(HitLocation);
        }
    }
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
    // find crosshair
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
    
    // de-project the screen position of crosshair to a world direction
    FVector CameraWorldLocation;
    FVector CameraWorldDirection;
    if (GetLookDirection(ScreenLocation, CameraWorldLocation, CameraWorldDirection))
    {
        //UE_LOG(LogTemp, Warning, TEXT("Look Direction is %s"), *CameraWorldDirection.ToString());     // unit vector
       
        // Line-Trace along said direction and get HitLocation
        return GetLookVectorHitLocation(CameraWorldDirection, HitLocation);
    }

    return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& CameraWorldLocation, FVector& CameraWorldDireciton) const
{        
    return DeprojectScreenPositionToWorld(
        ScreenLocation.X,
        ScreenLocation.Y,
        CameraWorldLocation,
        CameraWorldDireciton
    );
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector& CameraWorldDirection, FVector& HitLocation) const
{
    FHitResult HitResult;
    FVector CameraStartLocation = PlayerCameraManager->GetCameraLocation();
	FVector CameraLookLocation = CameraStartLocation + CameraWorldDirection * LineTraceRange;

    // /// Setup query parameters
	// FCollisionQueryParams TraceParameters(
	// 	FName(TEXT("")),
	// 	false,
	// 	GetOwner() // trace ignores owner
	// );

    // ECollisionResponse CollisionResponse;
    // FCollisionResponseParams ResponseParameters(CollisionResponse);

    if(GetWorld()->LineTraceSingleByChannel(
        HitResult,
        CameraStartLocation,
        CameraLookLocation,
        ECollisionChannel::ECC_Visibility))
        //TraceParameters,
        //ResponseParameters))
    {
        HitLocation = HitResult.Location;
        return true;
    }

    HitLocation = FVector(0);
    return false;
}
