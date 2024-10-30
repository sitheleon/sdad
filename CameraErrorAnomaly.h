#pragma once

#include "CoreMinimal.h"
#include "AnomalyBase.h"
#include "CameraErrorAnomaly.generated.h"

/**
 * 
 */
UCLASS()
class OBSERVATION2_API ACameraErrorAnomaly : public AAnomalyBase
{
    GENERATED_BODY()

public:
    ACameraErrorAnomaly();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    void TriggerAnomaly() override;
    void FixAnomaly() override;

    UPROPERTY(BlueprintReadOnly, Category = "Anomaly")
    bool bIsWidgetAnomalyOn;

    UPROPERTY(BlueprintReadOnly, Category = "Anomaly")
    bool bIsWidgetAnomalyFixed;

private:
    // 위젯 인스턴스
    UPROPERTY()
    UUserWidget* AnomalyWidgetInstance;

    // UMG 위젯 블루프린트 클래스를 에디터에서 설정할 수 있도록 선언
    UPROPERTY(EditAnywhere, Category = "Anomaly")
    TSubclassOf<UUserWidget> WidgetClass;
};
