// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
    Super::BeginPlay();

    ATank* TankAI = GetControlledTank();
    if (!TankAI)
    {
        UE_LOG(LogTemp, Warning, TEXT("AI Tank not possessd."));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AI possessing %s."), *TankAI->GetName());
    }

    ATank* PlayerTank = GetPlayerTank();
    if (PlayerTank)
    { 
        UE_LOG(LogTemp, Warning, TEXT("AI found Player %s."), *PlayerTank->GetName());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AI has no found PLayer Tank."));
    }
}


void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (GetPlayerTank())
    {
        GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
    }
}

ATank* ATankAIController::GetControlledTank() const    // take note of prefix "A"
{
    return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
    APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
    if (!PlayerPawn)
    {
        return nullptr;
    }
    return Cast<ATank>(PlayerPawn);
}