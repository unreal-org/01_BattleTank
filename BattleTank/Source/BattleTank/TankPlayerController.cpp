// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Engine/EngineTypes.h"
//#include "Public/CollisionQueryParams.h"


void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    ATank* ControlledTank = GetControlledTank();
    if (!ControlledTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank."));
    }
    else 
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing %s."), *ControlledTank->GetName());
    }
    UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play."));
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    AimTowardCrosshair();
}


ATank* ATankPlayerController::GetControlledTank() const    // take note of prefix "A"
{
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardCrosshair()
{
    if (!GetControlledTank())
    {
        return;
    }

    FVector HitLocation; // OUT parameter
    if (GetSightRayHitLocation(HitLocation))
    {
        //UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
        GetControlledTank()->AimAt(HitLocation);
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
        GetLookVectorHitLocation(CameraWorldDirection, HitLocation);
    }

    return true;
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
