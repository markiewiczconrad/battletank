// Copyright ConradCo

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

	public:
		void BeginPlay() override;
	
	private:
		virtual void Tick(float DeltaTime) override;

		float AcceptanceRadius = 3000;

		/*ATank* GetControlledTank() const;
	
		ATank* GetPlayerTank() const;*/
};
