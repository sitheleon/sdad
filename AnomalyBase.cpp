// Fill out your copyright notice in the Description page of Project Settings.

#include "AnomalyBase.h"

// 정적 변수 초기화
int32 AAnomalyBase::UnfixedAnamolyCount = 0;

AAnomalyBase::AAnomalyBase()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AAnomalyBase::BeginPlay()
{
    Super::BeginPlay();

    UnfixedAnamolyCount = 0;

}

void AAnomalyBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

FString AAnomalyBase::GetCurrentAnomalyInfo() const
{
    if (CurrentAnomaly.IsActive)
    {
        UE_LOG(LogTemp, Error, TEXT("위치: %s, 종류: %s"), *CurrentAnomaly.Place, *CurrentAnomaly.Type);
        return TEXT("현재 활성화된 이상 현상.");
    }
    else
    {
        return TEXT("현재 활성화된 이상 현상이 없습니다.");
    }
}

void AAnomalyBase::ResetCurrentAnomaly()
{
    CurrentAnomaly.IsActive = false;
    CurrentAnomaly.Place = TEXT("");
    CurrentAnomaly.Type = TEXT("");
}

FString AAnomalyBase::GetAnomalyLocation() const
{
    return CurrentAnomaly.Place;
}

FString AAnomalyBase::GetAnomalyType() const
{
    return CurrentAnomaly.Type;
}

int32 AAnomalyBase::GetUnfixedAnamolyCount()
{
    return UnfixedAnamolyCount;
}

