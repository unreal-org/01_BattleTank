// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "TankAimingComponent.h"


void ATankAIController::BeginPlay()
{
    Super::BeginPlay();

    // ATank* TankAI = GetControlledTank();
    // if (!TankAI)
    // {
    //     UE_LOG(LogTemp, Warning, TEXT("AI Tank not possessd."));
    // }
    // else
    // {
    //     UE_LOG(LogTemp, Warning, TEXT("AI possessing %s."), *TankAI->GetName());
    // }

    // ATank* PlayerTank = GetPlayerTank();
    // if (PlayerTank)
    // { 
    //     UE_LOG(LogTemp, Warning, TEXT("AI found Player %s."), *PlayerTank->GetName());
    // }
    // else
    // {
    //     UE_LOG(LogTemp, Warning, TEXT("AI has no found PLayer Tank."));
    // }
}


void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    APawn* PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn(); // no need to cast to atank anymore
    APawn* ControlledTank = GetPawn();

    if (!ensure(ControlledTank && PlayerTank)) { return; }

    MoveToActor(PlayerTank, AcceptanceRadius);      // (target, stop at this distance)
    // ControlledTank->AimAt(PlayerTank->GetActorLocation());
    // ControlledTank->Fire();

    UTankAimingComponent* AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if(!ensure(AimingComponent)) { return; }
    AimingComponent->AimAt(PlayerTank->GetActorLocation());
    
    // FIX FIRING / for aiming for locked
    //ControlledTank->Fire();
    if (AimingComponent->GetFiringStatus() == EFiringStatus::Locked)
    {
        AimingComponent->Fire();
    }
}

// ATank* ATankAIController::GetControlledTank() const    // take note of prefix "A"
// {
//     return Cast<ATank>(GetPawn());
// }

// ATank* ATankAIController::GetPlayerTank() const
// {
//     APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
//     if (!PlayerPawn)
//     {
//         return nullptr;
//     }
//     return Cast<ATank>(PlayerPawn);
// }