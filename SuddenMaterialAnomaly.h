// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnomalyBase.h"
#include "SuddenMaterialAnomaly.generated.h"

/**
 * 
 */
UCLASS()
class OBSERVATION2_API ASuddenMaterialAnomaly : public AAnomalyBase
{
	GENERATED_BODY()
public:
	ASuddenMaterialAnomaly();

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
