// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("TankPLayerController begin play!"))

		auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController is not possessing a tank."))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController is possessing tank: %s."), *ControlledTank->GetName())
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	///UE_LOG(LogTemp, Warning, TEXT("Ticking!"));
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation;	// OUT parameter
	if (GetSightRayHitLocation(HitLocation))
	{
		///UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *HitLocation.ToString());
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	///UE_LOG(LogTemp, Warning, TEXT("Screenlocation: %s"), *ScreenLocation.ToString())	// remove

	return true;
}


