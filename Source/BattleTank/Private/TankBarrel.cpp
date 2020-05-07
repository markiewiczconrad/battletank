// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed) {
	auto ElevationChange = FMath::Clamp(RelativeSpeed, -1.0f, 1.0f) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	SetRelativeRotation((FRotator(FMath::Clamp(RawNewElevation, MinElevation, MaxElevation), 0, 0)));
}