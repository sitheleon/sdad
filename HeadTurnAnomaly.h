// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnomalyBase.h"
#include "HeadTurnAnomaly.generated.h"

/**
 * 
 */
UCLASS()
class OBSERVATION2_API AHeadTurnAnomaly : public AAnomalyBase
{
	GENERATED_BODY()
public:
	AHeadTurnAnomaly();

	UPROPERTY(EditAnywhere, Category="Anomaly")
	float PitchValue;

	UPROPERTY(EditAnywhere, Category="Anomaly")
	float YawValue;

	UPROPERTY(EditAnywhere, Category="Anomaly")
	float RollValue;
	

protected:
	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;

	void TriggerAnomaly() override;

	void FixAnomaly() override;

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* AnomalyMesh;
	
};
