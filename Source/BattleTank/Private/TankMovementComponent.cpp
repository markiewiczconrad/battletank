// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) {

    LeftTrack = LeftTrackToSet;
    RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMove(float Throw) {
    if (!LeftTrack || !RightTrack) return;
    UE_LOG(LogTemp, Warning, TEXT("%f"), Throw);
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendRotate(float Throw) {
    if (!LeftTrack || !RightTrack) return;
    LeftTrack->SetThrottle(Throw * 2.0f);
    RightTrack->SetThrottle(Throw * -2.0f);
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity,bool bForceMaxSpeed) {
    auto Owner = GetOwner()->GetName();
    auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
    auto AIForwardIntention = MoveVelocity.GetSafeNormal();
    auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);

    UE_LOG(LogTemp, Warning, TEXT("%s: %s"), *Owner, *AIForwardIntention.ToString());

    IntendMove(ForwardThrow);
}