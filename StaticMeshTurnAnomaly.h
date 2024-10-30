// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnomalyBase.h"
#include "TimerManager.h"
#include "StaticMeshTurnAnomaly.generated.h"

/**
 * 
 */
UCLASS()
class OBSERVATION2_API AStaticMeshTurnAnomaly : public AAnomalyBase
{
	GENERATED_BODY()

public:
	AStaticMeshTurnAnomaly(); 

	virtual void TriggerAnomaly() override;	

	
	virtual void FixAnomaly() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Anomaly")
	class ACameraActor* TargetCamera;

protected:
	virtual void BeginPlay() override;

private:
	FRotator InitialRotation;

	void RotateToFaceCamera();

	FTimerHandle TimerHandle;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UStaticMeshComponent* MeshComponent;

};
