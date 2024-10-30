// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnomalyBase.h"
#include "FurnitureAnomaly.generated.h"

/**
 * 
 */
UCLASS()
class OBSERVATION2_API AFurnitureAnomaly : public AAnomalyBase
{
	GENERATED_BODY()

public:
	AFurnitureAnomaly(); 

    virtual void TriggerAnomaly() override;	

	
	virtual void FixAnomaly() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	FVector InitialLocation; //가구 초기 위치
	
};
