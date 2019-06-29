// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController   // child of AActor
{
	GENERATED_BODY()
	
private:
	virtual void BeginPlay() override;      // override AActor's virtual BeginPlay
	virtual void Tick(float DeltaTime) override;
	
	ATank* GetControlledTank() const;
	void AimTowardCrosshair();    // moves tank barrel to crosshair
		
	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5f;

	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.3333f;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 10000;

	bool GetSightRayHitLocation(FVector& HitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& CameraWorldLocation, FVector& CameraWorldDireciton) const;
	bool GetLookVectorHitLocation(FVector& CameraWorldDirection, FVector& HitLocation) const;
};	
