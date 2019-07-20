// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Actor.h"
#include "TankTrack.h"
#include "Math/Vector.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
    // if (!LeftTrackToSet || !RightTrackToSet){ return; }
    LeftTrack = LeftTrackToSet;
    RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
    // no need to call super - replacing functionality
    FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
    FVector AIForwardIntention = MoveVelocity.GetSafeNormal();

    float ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
    IntendMoveForward(ForwardThrow);

    float RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;   // cross order matters
    IntendTurnRight(RightThrow);
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
    if (!ensure(LeftTrack && RightTrack)) { return; }
    //UE_LOG(LogTemp, Warning, TEXT("IntendMoveForward() called with throw: %f"), Throw);
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(Throw);       // forward vector stacks with trigger throttles - FIX
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
     if (!ensure(LeftTrack && RightTrack)) { return; }
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(-Throw);       
}
