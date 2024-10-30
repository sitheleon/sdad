// Fill out your copyright notice in the Description page of Project Settings.


#include "StaticMeshTurnAnomaly.h"
#include "Engine/StaticMesh.h"
#include "Kismet/KismetMathLibrary.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"


AStaticMeshTurnAnomaly::AStaticMeshTurnAnomaly()
{
    PrimaryActorTick.bCanEverTick = true;
    
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    RootComponent = MeshComponent;
}


void AStaticMeshTurnAnomaly::BeginPlay()
{
    Super::BeginPlay();

    InitialRotation = GetActorRotation();
    MeshComponent->SetVisibility(false);
    
    // Log the initial rotation
    UE_LOG(LogTemp, Warning, TEXT("Initial Rotation: %s"), *InitialRotation.ToString());

    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), FoundActors);

    // Log the number of found actors
    UE_LOG(LogTemp, Warning, TEXT("Found %d camera actors."), FoundActors.Num());

    for (AActor* Actor : FoundActors)
    {
        // Log each actor's name
        UE_LOG(LogTemp, Warning, TEXT("Found Actor: %s"), *Actor->GetName());

        if (Actor->GetName() == "BP_Cam3_C_UAID_D843AE24536DC62202_1266467247")
        {
            TargetCamera = Cast<ACameraActor>(Actor);
            if (TargetCamera)
            {
                UE_LOG(LogTemp, Warning, TEXT("Target Camera found: %s"), *TargetCamera->GetName());
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Failed to cast to ACameraActor for actor: %s"), *Actor->GetName());
            }
            break;
        }
    }

    if (!TargetCamera)
    {
        UE_LOG(LogTemp, Error , TEXT("No target camera found with the name BP_Cam3."));
    }


    UE_LOG(LogTemp, Error, TEXT("Mesh Visibility: %s"), MeshComponent->IsVisible() ? TEXT("Visible") : TEXT("Hidden"));

}


void AStaticMeshTurnAnomaly::RotateToFaceCamera()
{
    if(TargetCamera)
    {
        FVector CameraLocation = TargetCamera->GetActorLocation();
        FVector DirectionToCamera = CameraLocation - GetActorLocation();
        DirectionToCamera.Normalize();

        FRotator NewRotation = DirectionToCamera.Rotation();
        SetActorRotation(NewRotation);

        UE_LOG(LogTemp, Warning, TEXT("Rotating to face camera"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("TargetCamera is not set"));
    }

}

void AStaticMeshTurnAnomaly::TriggerAnomaly()
{   
    Super::TriggerAnomaly();

    MeshComponent->SetVisibility(true);

    GetWorld()->GetTimerManager().SetTimer
    (TimerHandle, this, &AStaticMeshTurnAnomaly::RotateToFaceCamera, 3.0f, false);

    UnfixedAnamolyCount++;
}

void AStaticMeshTurnAnomaly::FixAnomaly()
{
    Super::FixAnomaly();

    MeshComponent->SetVisibility(false);

    UnfixedAnamolyCount--;
}

void AStaticMeshTurnAnomaly::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}


