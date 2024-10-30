#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ObservationPlayerCameraManager.h"
#include "CameraPlayerController.generated.h"

/**
 * A custom PlayerController for handling camera switching.
 */
UCLASS()
class ACameraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	ACameraPlayerController();

	virtual void SetupInputComponent() override;

	
	void UpdateTimer();

	UPROPERTY(BlueprintReadOnly)
	FString TimerText;

	UFUNCTION(BlueprintCallable)
	float CurrentCamera();

	float GetElapsedTime() const;


private:
	void SwitchToNextCamera();
	void SwitchToPreviousCamera();
		
	UPROPERTY()
	AObservationPlayerCameraManager* CameraManager;


	float ElapsedTime;
	FTimerHandle TimerHandle;

protected:
	virtual void BeginPlay() override;

};
