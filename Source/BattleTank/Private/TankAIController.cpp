// Copyright ConradCo

#include "Tank.h"
#include "TankAIController.h"

/*ATank* ATankAIController::GetControlledTank() const {
    return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const {
    auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
    if (!PlayerTank) return nullptr;
    return Cast<ATank>(PlayerTank);
}*/

void ATankAIController::BeginPlay() {
    Super::BeginPlay();

    //auto* owner = GetControlledTank();

    //if (!owner) return;

    //auto* player = GetPlayerTank();

    //UE_LOG(LogTemp, Warning, TEXT("AI Controller Begin Play."));
    //UE_LOG(LogTemp, Warning, TEXT("Owner is: %s"), *(owner->GetName()));
    //UE_LOG(LogTemp, Warning, TEXT("Player is: %s"), *(player->GetName()));
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());

	if (PlayerTank)
	{
		// Move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius); // TODO check radius is in cm

		// Aim towards the player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		//ControlledTank->Fire(); // TODO limit firing rate
	}
}