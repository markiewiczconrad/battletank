// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankMovementComponent.h"
#include "TankTrack.h"
#include "TankTurret.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aim Component"));

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector HitLocation) {
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::SetBarrelReference(UTankBarrel *BarrelToSet) {
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret *TurretToSet) {
	TankAimingComponent->SetTurretReference(TurretToSet);
}

void ATank::Fire() {
	

	bool isReloaded = ((FPlatformTime::Seconds() - lastFireTime) >= reloadTime);

	if (Barrel && isReloaded) {
		// Spawn a projectile at the socket location on the barrel;
		AProjectile *Projectile = GetWorld()->SpawnActor<AProjectile>(*ProjectileBlueprint, Barrel->GetSocketTransform(FName("Projectile")));
		Projectile->LaunchProjectile(LaunchSpeed);
		lastFireTime = FPlatformTime::Seconds();
	}
}