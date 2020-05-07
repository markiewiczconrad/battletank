// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankPlayerController.h"

ATank* ATankPlayerController::GetControlledTank() const {
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay() {
    Super::BeginPlay();

    auto* owner = GetControlledTank();

    if (!owner) return;

    //UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));
    //UE_LOG(LogTemp, Warning, TEXT("Owner is: %s"), *(owner->GetName()));
}

void ATankPlayerController::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
    AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair() {
    if (!GetControlledTank())
        return;

    FVector HitLocation;
    if (GetSightRayHitLocation(HitLocation)) {
        GetControlledTank()->AimAt(HitLocation);
        // Get world location through crosshair
        // If it hits something, get controlled tank to aim at this point.
    }
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const {
    // Get the player's position and draw a ray through the crosshair, then assign it to HitLocation
    // Find crosshair position
    int32 ViewportSize_x, ViewportSize_y;
    GetViewportSize(ViewportSize_x, ViewportSize_y);

    auto ScreenLocation = FVector2D(ViewportSize_x * Crosshair_x, ViewportSize_y * Crosshair_y);
    FVector Camera_Direction;
    // De-project the screen position of the crosshair to a world direction
    if(GetLookDirection(ScreenLocation, Camera_Direction))
        GetLookVectorHitLocation(Camera_Direction, OutHitLocation);
    // Line-trace alone that direction, and see what we hit.
    return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector &Camera_Direction) const {
    FVector Camera_Location;
    return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, Camera_Location, Camera_Direction);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const {
    FHitResult HitResult;
    auto StartLocation = PlayerCameraManager->GetCameraLocation();
    auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
    if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility))
    {
        HitLocation = HitResult.Location;
        return true;
    }
    return false;
}