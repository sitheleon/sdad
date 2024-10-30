// Fill out your copyright notice in the Description page of Project Settings.


#include "SkeletalMeshAnomaly.h"
#include "CameraPlayerController.h"




ASkeletalMeshAnomaly::ASkeletalMeshAnomaly()
{   
    SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
    RootComponent = SkeletalMesh;


    PrimaryActorTick.bCanEverTick = true;
}

void ASkeletalMeshAnomaly::BeginPlay()
{
    Super::BeginPlay();

    SkeletalMesh->SetVisibility(false);

    bIsAnomalyOn = false;

    // 플레이어 컨트롤러 접근

    /*
    GetWorld()->GetFirstPlayerController()를 호출하여 현재 게임에서 
    활성화된 첫 번째 플레이어 컨트롤러를 가져옵니다. 
    그 후 Cast를 사용하여 
    해당 플레이어 컨트롤러가 ACameraPlayerController 타입인지 확인합니다.
    */
    ACameraPlayerController* PlayerController = Cast<ACameraPlayerController>(GetWorld()->GetFirstPlayerController());
    if (PlayerController)
    {
        TimePassed = PlayerController->GetElapsedTime();
    }
    else
    {
        // 플레이어 컨트롤러가 유효하지 않을 경우의 처리
        UE_LOG(LogTemp, Warning, TEXT("PlayerController is not valid!"));
    }
}


void ASkeletalMeshAnomaly::TriggerAnomaly()
{   
    Super::TriggerAnomaly();
    
        SkeletalMesh->SetVisibility(true);
        UnfixedAnamolyCount++;
        bIsAnomalyOn = true;
    
}

void ASkeletalMeshAnomaly::FixAnomaly()
{   
    Super::FixAnomaly();

    SkeletalMesh->SetVisibility(false); 
    UnfixedAnamolyCount--;
    bIsAnomalyOn= false;
}

void ASkeletalMeshAnomaly::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}




