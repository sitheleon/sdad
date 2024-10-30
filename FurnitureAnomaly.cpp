// Fill out your copyright notice in the Description page of Project Settings.


#include "FurnitureAnomaly.h"



AFurnitureAnomaly::AFurnitureAnomaly()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AFurnitureAnomaly::BeginPlay()
{
    Super::BeginPlay();
    
    // 가구의 초기 위치를 저장
    InitialLocation = GetActorLocation();
}

void AFurnitureAnomaly::TriggerAnomaly()
{
    Super::TriggerAnomaly();
    // 새로운 랜덤 위치로 가구 이동
    FVector RandomOffset = FVector(FMath::RandRange(-60.0f, 60.0f), FMath::RandRange(-60.0f, 60.0f), 0.0f);
    SetActorLocation(InitialLocation + RandomOffset);

    UnfixedAnamolyCount++;

}

void AFurnitureAnomaly::FixAnomaly()
{
    Super::FixAnomaly();
    SetActorLocation(InitialLocation);

    UnfixedAnamolyCount--;

    
}