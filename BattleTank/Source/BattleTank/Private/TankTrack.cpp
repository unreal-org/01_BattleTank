// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"
#include "Math/UnrealMathUtility.h"
#include "Components/SceneComponent.h"
#include "Math/Vector.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"
#include "Math/UnrealMathUtility.h"

UTankTrack::UTankTrack()
{
    PrimaryComponentTick.bCanEverTick = false;  // no need anymore
}

void UTankTrack::BeginPlay()
{
    Super::BeginPlay();
    OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{   // bad idea to use boolean here
    // drive the tracks and apply sideways friction
    DriveTrack();
    ApplySidewaysForce();
    CurrentThrottle = 0;  // reset currentthrottle
}

void UTankTrack::ApplySidewaysForce()
{
    // calculate slippage speed
    float SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
    // work out required accleration this frame to correct
    float DeltaTime = GetWorld()->GetDeltaSeconds();
    FVector CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
    // apply force sideways (F = M * A)
    UStaticMeshComponent* TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
    FVector CorrectionForce = TankRoot->GetMass() * CorrectionAcceleration / 2;   // per track
    TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // // calculate slippage speed
    // float SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
    // // work out required accleration this frame to correct
    // FVector CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
    // // apply force sideways (F = M * A)
    // UStaticMeshComponent* TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
    // FVector CorrectionForce = TankRoot->GetMass() * CorrectionAcceleration / 2;   // per track
    // TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
    // FString Name = GetName();
    // UE_LOG(LogTemp, Warning, TEXT("%s throttling."), *Name);

    // FVector ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
    // FVector ForceLocation = GetComponentLocation();
    // UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    // TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
    CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTrack::DriveTrack()
{
    FVector ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
    FVector ForceLocation = GetComponentLocation();
    UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}