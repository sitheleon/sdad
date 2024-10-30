// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CameraManager.h"
#include "CameraPlayerController.h" 
#include "OBSERVATION2GameMode.generated.h"

UCLASS(minimalapi)
class AOBSERVATION2GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AOBSERVATION2GameMode();

	// Camera Manager reference
	UPROPERTY(BlueprintReadWrite, Category = "Camera")
	ACameraManager* CameraManagerRef;

protected:

	virtual void BeginPlay() override;


};



