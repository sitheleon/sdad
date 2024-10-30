// Fill out your copyright notice in the Description page of Project Settings.


#include "SuddenAnomaly.h"


ASuddenAnomaly::ASuddenAnomaly()
{
    PrimaryActorTick.bCanEverTick = true;

    AnomalyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AnomalyMesh"));
    RootComponent = AnomalyMesh;
}



void ASuddenAnomaly::BeginPlay()
{
    Super::BeginPlay();

    AnomalyMesh->SetVisibility(false);
}

void ASuddenAnomaly::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ASuddenAnomaly::TriggerAnomaly()
{
    Super::TriggerAnomaly();

    AnomalyMesh->SetVisibility(true);

    UnfixedAnamolyCount++;
    //UE_LOG(LogTemp, Error, TEXT("UnFixedAnomalyCount: %d"),  UnfixedAnamolyCount);

}

void ASuddenAnomaly::FixAnomaly()
{
    AnomalyMesh->SetVisibility(false);

    UnfixedAnamolyCount--;
    //UE_LOG(LogTemp, Error, TEXT("UnFixedAnomalyCount: %d"),  UnfixedAnamolyCount);
}

