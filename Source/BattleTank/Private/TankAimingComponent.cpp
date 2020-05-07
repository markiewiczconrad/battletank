// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) {
	if (!Barrel && !Turret) return;

	FVector TossVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		TossVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace);
	if(bHaveAimSolution) {
		auto AimDesiredDirection = TossVelocity.GetSafeNormal();
		auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution found"), Time);
		MoveBarrelTowards(AimDesiredDirection);
	}
	else
	{
		auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f: No aim solve found"), Time);
	}
	
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel *BarrelToSet) {
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret *TurretToSet) {
	Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector Direction) {
	//Work out difference between current barrel position & desired position
	//UE_LOG(LogTemp, Warning, TEXT("Aiming at %s"), *Direction.ToString());
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimRotator = Direction.Rotation();
	auto DeltaRotator = AimRotator - BarrelRotator;
	//Move the barrel towards this direction

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}