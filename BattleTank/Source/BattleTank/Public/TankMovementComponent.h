// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )   // to add tank movement in blueprint
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BluePrintCallable, Category = "Setup")      // initialize in input setup
	void Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

	UFUNCTION(BluePrintCallable, Category = "Input")
	void IntendMoveForward(float Throw);

	UFUNCTION(BluePrintCallable, Category = "Input")
	void IntendTurnRight(float Throw);
	
	
private:
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;
	
	// check best protection
	virtual void RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed) override;

};
