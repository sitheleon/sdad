#include "CameraErrorAnomaly.h"
#include "Blueprint/UserWidget.h"

ACameraErrorAnomaly::ACameraErrorAnomaly()
{
    PrimaryActorTick.bCanEverTick = true;

    // 변수 초기화
    bIsWidgetAnomalyOn = false;
    bIsWidgetAnomalyFixed = true; // 시작할 때 위젯이 고정된 상태
}

void ACameraErrorAnomaly::BeginPlay()
{
    Super::BeginPlay();

    // 위젯 클래스가 설정되어 있는지 확인
    if (WidgetClass)
    {
        // 위젯 인스턴스 생성
        AnomalyWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
        
        if (AnomalyWidgetInstance)
        {
            UE_LOG(LogTemp, Warning, TEXT("AnomalyWidgetInstance successfully created."));
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to create AnomalyWidgetInstance."));
        }
    }
}

void ACameraErrorAnomaly::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ACameraErrorAnomaly::TriggerAnomaly()
{   
    Super::TriggerAnomaly();

    if (AnomalyWidgetInstance && !bIsWidgetAnomalyOn)
    {
        // 위젯을 화면에 추가
        AnomalyWidgetInstance->AddToViewport();   bIsWidgetAnomalyOn = true;
        bIsWidgetAnomalyFixed = false; // 이상이 발생했으므로 고정 상태를 false로 변경
        UE_LOG(LogTemp, Warning, TEXT("Anomaly triggered: Widget is now visible on the viewport."));
        UnfixedAnamolyCount++;
    }
}

void ACameraErrorAnomaly::FixAnomaly()
{   

    Super::FixAnomaly();

    if (AnomalyWidgetInstance && bIsWidgetAnomalyOn)
    {
        // 위젯을 화면에서 제거 .. 하나?

         AnomalyWidgetInstance->RemoveFromParent();
        bIsWidgetAnomalyOn = false;
        bIsWidgetAnomalyFixed = true; // 이상이 고쳐졌으므로 고정 상태를 true로 변경
        UE_LOG(LogTemp, Warning, TEXT("Anomaly fixed: Widget is now hidden from the viewport."));
         UnfixedAnamolyCount--;
    }
}
