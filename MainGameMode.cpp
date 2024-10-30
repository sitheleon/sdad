// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "AnomalyBase.h" // AAnomalyBase 클래스 포함
#include "Blueprint/UserWidget.h" // UUserWidget 클래스 포함
#include "Kismet/GameplayStatics.h" // GameplayStatics 클래스 포함
#include "CameraPlayerController.h"


#include "CameraPlayerController.h"

AAnomalyBase* AnomalyCount;


AMainGameMode::AMainGameMode()
{
    PrimaryActorTick.bCanEverTick = true;
}

bool AMainGameMode::CheckIfRightKeyIsDown()
{
    if(bIsRightKeyDown)
    {
        return true;
    }
    else
    {
        return false;
    }
}


void AMainGameMode::EndGame()
{   
    if (AnomalyCount == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("AnomalyCount is null"));
        return;
    }

    //UE_LOG(LogTemp, Warning, TEXT("UnfixedAnamolyCount: %d"), AnomalyCount->UnfixedAnamolyCount);

    if (AnomalyCount->UnfixedAnamolyCount >= 60)
    {
        bIsGameOver = true;
        //UE_LOG(LogTemp, Warning, TEXT("게임 오버"));
        //UE_LOG(LogTemp, Warning, TEXT("bIsGameOver: %d"), bIsGameOver);
    }
    else
    {
        bIsGameOver = false;
        //UE_LOG(LogTemp, Warning, TEXT("게임 계속 진행"));
    }
}

void AMainGameMode::WinGame()
{   
    // 플레이어 컨트롤러에서 직접 GetElapsedTime() 호출
    if (ACameraPlayerController* CameraController = Cast<ACameraPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
    {
        CurrentTime = CameraController->GetElapsedTime();
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("CameraController is null"));
    }
                        //6시
    if(CurrentTime >= 360)
    {
        bIsPlayerWinner = true;
    }
    else
    {
        bIsPlayerWinner = false;
    }
}





void AMainGameMode::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    CheckIfRightKeyIsDown();

    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

    if(PlayerController && PlayerController->WasInputKeyJustPressed(EKeys::Right))
    {
        bIsRightKeyDown = true;
    }

    EndGame();
   // UE_LOG(LogTemp, Error, TEXT("EndGame Function Called") );

    WinGame();
}



void AMainGameMode::BeginPlay()
{
    Super::BeginPlay();

    RandomTime = FMath::RandRange(100.0f, 300.0f);

    bIsRightKeyDown = false;

    // 게임 시작 시 AnomalyCount를 찾음 (맵에 배치된 첫 번째 AnomalyBase 인스턴스를 가져옴)
    TArray<AActor*> FoundAnomalies;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAnomalyBase::StaticClass(), FoundAnomalies);

    if (FoundAnomalies.Num() > 0)
    {
        AnomalyCount = Cast<AAnomalyBase>(FoundAnomalies[0]);  // 첫 번째 AnomalyBase 인스턴스를 참조
        UE_LOG(LogTemp, Warning, TEXT("AnomalyCount 초기화 성공"));
    }
    else
    {
        AnomalyCount = nullptr;
        UE_LOG(LogTemp, Error, TEXT("AnomalyCount 초기화 실패"));
    }

    bIsGameOver = false;
    bIsPlayerWinner = false;
}

