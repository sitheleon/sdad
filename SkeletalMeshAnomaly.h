// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnomalyBase.h"
#include "SkeletalMeshAnomaly.generated.h"

/**
 * 
 */
UCLASS()
class OBSERVATION2_API ASkeletalMeshAnomaly : public AAnomalyBase
{
	GENERATED_BODY()


public:
	ASkeletalMeshAnomaly(); 

    virtual void TriggerAnomaly() override;	

	
	virtual void FixAnomaly() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Anomaly")
	class USkeletalMeshComponent* SkeletalMesh;

	float TimePassed;

	UPROPERTY(BlueprintReadOnly, Category = "Anomaly")
	bool bIsAnomalyOn;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	
};
