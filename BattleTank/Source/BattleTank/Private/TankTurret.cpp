// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"
#include "Math/Rotator.h"
#include "Components/SceneComponent.h"
#include "Math/UnrealMathUtility.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
    // move turret said difference
    // given max elevation speed and frame time
    RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
    float RotationChange = RelativeSpeed * MaxDegreePerSecond * GetWorld()->DeltaTimeSeconds;
    float NewRotation = RelativeRotation.Yaw + RotationChange;    // relativerotation is member variable
    
    SetRelativeRotation(FRotator(0, NewRotation, 0));
}