// Fill out your copyright notice in the Description page of Project Settings.


#include "SuddenMaterialAnomaly.h"


ASuddenMaterialAnomaly::ASuddenMaterialAnomaly()
{
    PrimaryActorTick.bCanEverTick = true;

      // Plane 메쉬를 생성
    AnomalyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AnomalyMesh"));
    RootComponent = AnomalyMesh;

    // Plane 메쉬를 로드하여 설정
    static ConstructorHelpers::FObjectFinder<UStaticMesh> PlaneMesh(TEXT("/Engine/BasicShapes/Plane.Plane"));
    if (PlaneMesh.Succeeded())
    {
        AnomalyMesh->SetStaticMesh(PlaneMesh.Object);
    }
}
void ASuddenMaterialAnomaly::BeginPlay()
{
    Super::BeginPlay();
    AnomalyMesh->SetVisibility(false);
}

void ASuddenMaterialAnomaly::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);


}

void ASuddenMaterialAnomaly::TriggerAnomaly()
{   
    Super::TriggerAnomaly();

    AnomalyMesh->SetVisibility(true);
    UnfixedAnamolyCount++;
    //UE_LOG(LogTemp, Error, TEXT("UnFixedAnomalyCount: %d"), UnfixedAnamolyCount);
}

void ASuddenMaterialAnomaly::FixAnomaly()
{
    Super::FixAnomaly();

    AnomalyMesh->SetVisibility(false);
    UnfixedAnamolyCount--;
    //UE_LOG(LogTemp, Error, TEXT("UnFixedAnomalyCount: %d"), UnfixedAnamolyCount);
}
