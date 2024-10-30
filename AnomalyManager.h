// AnomalyManager.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AnomalyBase.h"
#include "AnomalyManager.generated.h"

USTRUCT(BlueprintType)
struct FAnomalyManagerInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Place;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Type;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool IsActive;

    FAnomalyManagerInfo() : Place(""), Type(""), IsActive(false) {}
};

UCLASS()
class OBSERVATION2_API AAnomalyManager : public AActor
{
    GENERATED_BODY()
    
public:
    AAnomalyManager();

    UPROPERTY(BlueprintReadOnly)
    bool BIsAnomalyTriggered;

    UFUNCTION(BlueprintCallable, Category = "Anomaly")
    bool IsCurrentAnomaly(FString Place, FString Type, FString CurrentAnomalyStr);

    UFUNCTION(BlueprintCallable, Category = "Anomaly")
    FString GetCurrentAnomalyInfo() const;

    UFUNCTION(BlueprintCallable, Category = "Anomaly")
    void ResetCurrentAnomaly();



    UFUNCTION(BlueprintCallable, Category = "Anomaly")
    AAnomalyBase* GetCurrentAnomalyObject();

    float CurrentElapsedTime;

protected:
    virtual void BeginPlay() override;

private:
    FTimerHandle AnomalyTimerHandle;

    UPROPERTY(EditAnywhere, Category="Anomalies")
    TArray<AAnomalyBase*> Anomalies;

    UPROPERTY()
    FAnomalyManagerInfo CurrentAnomaly;

    void TriggerRandomAnomaly();
    void StartAnomalyTimer();

    int32 LastAnomalyIndex = -1;
};