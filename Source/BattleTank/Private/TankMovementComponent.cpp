// Copyright ConradCo


#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) {

    LeftTrack = LeftTrackToSet;
    RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMove(float Throw) {
    if (!LeftTrack || !RightTrack) return;
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendRotate(float Throw) {
    if (!LeftTrack || !RightTrack) return;
    LeftTrack->SetThrottle(Throw * 2.0f);
    RightTrack->SetThrottle(Throw * -2.0f);
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity,bool bForceMaxSpeed) {
    auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
    auto AIForwardIntention = MoveVelocity.GetSafeNormal();
    auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
    auto RotateThrow = FVector::CrossProduct(TankForward, AIForwardIntention);

    this->IntendMove(ForwardThrow);
    this->IntendRotate(1.5 * RotateThrow.Z);
}