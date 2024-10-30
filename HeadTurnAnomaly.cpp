// Fill out your copyright notice in the Description page of Project Settings.


#include "HeadTurnAnomaly.h"


AHeadTurnAnomaly::AHeadTurnAnomaly()
{
    PrimaryActorTick.bCanEverTick = true;
    AnomalyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AnomalyMesh"));
    RootComponent = AnomalyMesh;        
}

void AHeadTurnAnomaly::BeginPlay()
{
    Super::BeginPlay();

    AnomalyMesh->SetVisibility(false);
}

void AHeadTurnAnomaly::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    FRotator NewRotation = FRotator(PitchValue, YawValue, RollValue);

    FQuat QuatRotation = FQuat(NewRotation);

    AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
}

void AHeadTurnAnomaly::TriggerAnomaly()
{
    Super::TriggerAnomaly();

    AnomalyMesh->SetVisibility(true);
    UnfixedAnamolyCount++;
}

void AHeadTurnAnomaly::FixAnomaly()
{
    Super::FixAnomaly();

    AnomalyMesh->SetVisibility(false);
    UnfixedAnamolyCount--;
}
