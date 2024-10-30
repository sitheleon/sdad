// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "Camera/CameraActor.h"
#include "GameFramework/PlayerController.h"
#include "ObservationPlayerCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class OBSERVATION2_API AObservationPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()


	public:	
	// Sets default values for this actor's properties
	AObservationPlayerCameraManager(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "Camera")
	void SwitchToNextCamera();

	UFUNCTION(BlueprintCallable, Category = "Camera")
	void SwitchToPreviousCamera();

	void SwitchToCamera(int32 CameraIndex);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	float CurrentCamera();

	UPROPERTY()
	APlayerController* PlayerController;

	UPROPERTY(BlueprintReadOnly)
	bool IsCameraSwitched;


	

private:
	// 카메라 저장 배열
	UPROPERTY(EditAnywhere)
	TArray<AActor*> Cameras;

	int32 CurrentCameraIndex;

	
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	class USoundBase* CameraSwitchSound;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
