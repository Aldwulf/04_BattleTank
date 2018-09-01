// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"


void UTankTurret::Rotate(float RelativeRotateSpeed)
{
	///UE_LOG(LogTemp, Warning, TEXT("Rotate function called"))
	RelativeRotateSpeed = FMath::Clamp<float>(RelativeRotateSpeed, -1, 1);

	auto AzimuthChange = RelativeRotateSpeed * MaxRotationPerSecond * GetWorld()->DeltaTimeSeconds;
	auto Rotation = RelativeRotation.Yaw + AzimuthChange;

	SetRelativeRotation(FRotator(0, Rotation, 0));
}

