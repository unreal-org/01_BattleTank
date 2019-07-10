// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"
#include "Math/UnrealMathUtility.h"
#include "Components/SceneComponent.h"
#include "Math/Vector.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"

void UTankTrack::SetThrottle(float Throttle)
{
    // FString Name = GetName();
    // UE_LOG(LogTemp, Warning, TEXT("%s throttling."), *Name);

    FVector ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
    FVector ForceLocation = GetComponentLocation();
    UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}