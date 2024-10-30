// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnomalyBase.h"
#include "SuddenAnomaly.generated.h"

/**
 * 
 */
UCLASS()
class OBSERVATION2_API ASuddenAnomaly : public AAnomalyBase
{
	GENERATED_BODY()

public:
	ASuddenAnomaly();

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



	

