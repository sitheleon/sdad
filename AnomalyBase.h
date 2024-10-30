// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AnomalyBase.generated.h"

// FAnomalyInfo 구조체 정의
USTRUCT(BlueprintType)
struct FAnomalyInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Place;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Type;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool IsActive;

    FAnomalyInfo() : Place(""), Type(""), IsActive(false) {}
};

UCLASS()
class OBSERVATION2_API AAnomalyBase : public AActor
{
    GENERATED_BODY()
    
public:    
    AAnomalyBase();

    static int32 UnfixedAnamolyCount;

    virtual void TriggerAnomaly() PURE_VIRTUAL(AAnomalyBase::TriggerAnomaly, ;);

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FAnomalyInfo CurrentAnomaly;

    UFUNCTION(BlueprintCallable, Category = "Anomaly")
    FString GetCurrentAnomalyInfo() const;

    UFUNCTION(BlueprintCallable, Category = "Anomaly")
    void ResetCurrentAnomaly();

    UFUNCTION(BlueprintCallable, Category = "Anomaly")
    virtual FString GetAnomalyLocation() const;

    UFUNCTION(BlueprintCallable, Category = "Anomaly")
    virtual FString GetAnomalyType() const;


    UFUNCTION(BlueprintCallable, Category="Anomaly")
    virtual void FixAnomaly() PURE_VIRTUAL(AAnomalyBase::FixAnomaly, ;);

    int32 GetUnfixedAnamolyCount();

protected:
    virtual void BeginPlay() override;


public:    
    virtual void Tick(float DeltaTime) override;
};