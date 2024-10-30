#include "AnomalyManager.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "TimerManager.h"
#include "CameraPlayerController.h"

AAnomalyManager::AAnomalyManager()
{
    PrimaryActorTick.bCanEverTick = true;
    UE_LOG(LogTemp, Warning, TEXT("AAnomalyManager 생성자 호출"));
}

void AAnomalyManager::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("AAnomalyManager BeginPlay 시작"));

    CurrentElapsedTime = 0.0f;

    if (UWorld* World = GetWorld())
    {
        for (TActorIterator<AAnomalyBase> It(World); It; ++It)
        {
            Anomalies.Add(*It);
        }
        UE_LOG(LogTemp, Warning, TEXT("총 %d개의 AAnomalyBase 액터를 찾았습니다."), Anomalies.Num());
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("World를 가져오는데 실패했습니다."));
    }

    StartAnomalyTimer();
    UE_LOG(LogTemp, Warning, TEXT("AAnomalyManager BeginPlay 종료"));
}

void AAnomalyManager::StartAnomalyTimer()
{
    float RandomTime = FMath::RandRange(20.0f, 35.0f);

    ACameraPlayerController* PlayerController = Cast<ACameraPlayerController>(GetWorld()->GetFirstPlayerController());

    if(PlayerController)
    {
        CurrentElapsedTime = PlayerController->GetElapsedTime();
    }
                            //3시
    if(FMath::IsNearlyEqual(CurrentElapsedTime, 180.0f, 0.1f))
    {   
        // more often
        RandomTime = FMath::RandRange(15.0f, 30.0f); // in game 3 minute
        UE_LOG(LogTemp, Warning, TEXT("ElapsedTime이 180초에 도달하여 더 자주 발생: %.2f초 후"), RandomTime);
    }
    
                            //5시
    if(FMath::IsNearlyEqual(CurrentElapsedTime, 300.0f, 0.1f))
    {   
        // more often
        RandomTime = FMath::RandRange(13.0f, 25.0f); // in game 3 minute
        UE_LOG(LogTemp, Warning, TEXT("ElapsedTime이 300초에 도달하여 더 자주 발생: %.2f초 후"), RandomTime);
    }

    GetWorldTimerManager().SetTimer(AnomalyTimerHandle, this, &AAnomalyManager::TriggerRandomAnomaly, RandomTime, false);
    UE_LOG(LogTemp, Warning, TEXT("다음 이상 현상 타이머 설정: %.2f초 후"), RandomTime);
}

void AAnomalyManager::TriggerRandomAnomaly()
{
    UE_LOG(LogTemp, Warning, TEXT("TriggerRandomAnomaly 함수 호출"));
    
    if (Anomalies.Num() > 0)
    {
        int32 RandomIndex = FMath::RandRange(0, Anomalies.Num() - 1);
        AAnomalyBase* SelectedAnomaly = Anomalies[RandomIndex];
        
        // 이전에 선택된 인덱스와 동일하면 다시 선택
        while (RandomIndex == LastAnomalyIndex && Anomalies.Num() > 1)
        {
            RandomIndex = FMath::RandRange(0, Anomalies.Num() - 1);
            SelectedAnomaly = Anomalies[RandomIndex];
        }

        if (SelectedAnomaly)
        {
            UE_LOG(LogTemp, Warning, TEXT("이상 현상 발생: %s"), *SelectedAnomaly->GetName());
            SelectedAnomaly->TriggerAnomaly();

            CurrentAnomaly.Place = SelectedAnomaly->GetAnomalyLocation();
            CurrentAnomaly.Type = SelectedAnomaly->GetAnomalyType();
            CurrentAnomaly.IsActive = true;

            BIsAnomalyTriggered = true;

            // 마지막으로 트리거된 이상 현상 인덱스 업데이트
            LastAnomalyIndex = RandomIndex;
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("선택된 이상 현상이 유효하지 않습니다."));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("활성화할 이상 현상이 없습니다."));
    }
    
    StartAnomalyTimer();
}


bool AAnomalyManager::IsCurrentAnomaly(FString Place, FString Type, FString CurrentAnomalyStr)
{
    if (CurrentAnomaly.IsActive)
    {
        return (CurrentAnomaly.Place == Place && CurrentAnomaly.Type == Type);
    }
    else
    {
        return false;
    }
}


FString AAnomalyManager::GetCurrentAnomalyInfo() const
{
    if (CurrentAnomaly.IsActive)
    {
        return FString::Printf(TEXT("위치: %s, 종류: %s"), *CurrentAnomaly.Place, *CurrentAnomaly.Type);
    }
    else
    {
        return TEXT("현재 활성화된 이상 현상이 없습니다.");
    }
}

void AAnomalyManager::ResetCurrentAnomaly()
{
    CurrentAnomaly.IsActive = false;
    CurrentAnomaly.Place = TEXT("");
    CurrentAnomaly.Type = TEXT("");
    BIsAnomalyTriggered = false;
}




AAnomalyBase* AAnomalyManager::GetCurrentAnomalyObject()
{
    if (CurrentAnomaly.IsActive)
    {
        AAnomalyBase** FoundAnomaly = Anomalies.FindByPredicate([this](AAnomalyBase* Anomaly) {
            return Anomaly->GetAnomalyLocation() == CurrentAnomaly.Place &&
                   Anomaly->GetAnomalyType() == CurrentAnomaly.Type;
        });

        return FoundAnomaly ? *FoundAnomaly : nullptr;
    }
    return nullptr;
}