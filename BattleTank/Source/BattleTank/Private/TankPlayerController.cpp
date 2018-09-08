// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	///UE_LOG(LogTemp, Warning, TEXT("TankPLayerController begin play!"))

	auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if (AimingComponent)
	{
		FoundAimingComponent(AimingComponent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller cannot find Aiming COmponent at BeginPlay"))
	}

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
	// this code might be redundant now
}

void ATankPlayerController::AimTowardsCrosshair()
{
	//if (!GetControlledTank()) { return; }
	if (!GetPawn()) { return; }

	FVector HitLocation;	// OUT parameter
	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	///UE_LOG(LogTemp, Warning, TEXT("Screenlocation: %s"), *ScreenLocation.ToString())	// remove

	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		///UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *LookDirection.ToString()); // remove
		GetLookVectorHitLocation(LookDirection, HitLocation);
	}

	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldPosition;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldPosition, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + LookDirection * LineTraceRange;

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	else
	{
		HitLocation = FVector(0.0f);
		return false;
	}
}