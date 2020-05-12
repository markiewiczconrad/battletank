// Copyright ConradCo

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringStatus : uint8
{
	RELOADING,
	AIMING,
	LOCKED
};

class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	
	void AimAt(FVector HitLocation, float LaunchSpeed);

	void SetBarrelReference(UTankBarrel *BarrelToSet);

	void SetTurretReference(UTankTurret *TurretToSet);

protected:
	UPROPERTY( BlueprintReadOnly , Category = "State")
	EFiringStatus FiringState = EFiringStatus::RELOADING;

private:	
	bool bWantsBeginPlay;
	
	UTankBarrel *Barrel = nullptr;

	UTankTurret *Turret = nullptr;
		
	void MoveBarrelTowards(FVector Direction);
};
