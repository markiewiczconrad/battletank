// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

	private:
		ATank* GetControlledTank() const;

		void BeginPlay() override;

		virtual void Tick(float DeltaTime) override;

		void AimTowardsCrosshair();

		bool GetSightRayHitLocation(FVector &OutHitLocation) const;

		bool GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const;

		bool GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const;

		//UPROPERTY( EditAnywhere )
		float Crosshair_x = 0.5f;
		//UPROPERTY( EditAnywhere )
		float Crosshair_y = 0.3f;
		//UPROPERTY( EditAnywhere )
		int LineTraceRange = 1000000;

};
