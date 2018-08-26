// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("TankAIController begins play!"));

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController is not possessing a tank."))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController is possessing tank: %s."), *ControlledTank->GetName())
	}

	if (!GetPlayerController())
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot find PlayerController!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI tank %s reporting! PlayerController found! ID: %s"), *ControlledTank->GetName(), *GetPlayerController()->GetName())
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	///UE_LOG(LogTemp, Warning, TEXT("Ticking!"));

	GetControlledTank()->AimAt(GetPlayerController()->GetActorLocation());
	//UE_LOG(LogTemp, Warning, TEXT("%s is aiming at "), *GetControlledTank()->GetName())
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerController() const
{
	auto FoundPlayerController = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!FoundPlayerController) { return nullptr; }

	return Cast<ATank>(FoundPlayerController);
}