// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"
#include "Math/Rotator.h"
#include "Components/SceneComponent.h"
#include "Math/UnrealMathUtility.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
    // move barrel said difference
    // given max elevation speed and frame time
    RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
    float ElevationChange = RelativeSpeed * MaxDegreePerSecond * GetWorld()->DeltaTimeSeconds;
    float RawNewElevation = RelativeRotation.Pitch + ElevationChange;    // relativerotation is member variable
    float Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);

    SetRelativeRotation(FRotator(Elevation, 0, 0));
}