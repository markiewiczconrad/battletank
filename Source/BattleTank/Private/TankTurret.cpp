// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed) {
    auto RotationChange = FMath::Clamp(RelativeSpeed, -1.0f, 1.0f) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    auto RawNewRotation = RelativeRotation.Yaw + RotationChange;

    SetRelativeRotation(FRotator(0, RawNewRotation, 0));
}