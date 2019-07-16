// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Tank.h"
//#include "TankAimingComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController   // child of AActor
{
	GENERATED_BODY()
	
protected:
	//UFUNCTION(BlueprintCallable, Category = "Setup")
	//ATank* GetControlledTank() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimCompRef);

private:
	virtual void BeginPlay() override;      // override AActor's virtual BeginPlay
	virtual void Tick(float DeltaTime) override;

	void AimTowardCrosshair();    // moves tank barrel to crosshair
		
	UPROPERTY(EditDefaultsOnly)
	float CrosshairXLocation = 0.5f;

	UPROPERTY(EditDefaultsOnly)
	float CrosshairYLocation = 0.3333f;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 10000;

	bool GetSightRayHitLocation(FVector& HitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& CameraWorldLocation, FVector& CameraWorldDireciton) const;
	bool GetLookVectorHitLocation(FVector& CameraWorldDirection, FVector& HitLocation) const;
};	
