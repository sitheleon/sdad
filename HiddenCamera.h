// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "HiddenCamera.generated.h"

/**
 * 
 */
UCLASS()
class OBSERVATION2_API AHiddenCamera : public ACameraActor
{
	GENERATED_BODY()
	

public:

	AHiddenCamera();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Hidden Camera")
	void ShowHiddenCamera();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hidden Camera")
	bool bIsVisible;

private:
	UPROPERTY()
	class ACameraActor* CameraActor;

	UPROPERTY(EditAnywhere, Category = "Hidden Camera")
    TSubclassOf<ACameraActor> CameraClass;


	// Widget class reference

	class UUserWidget* WidgetInstance;

    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<UUserWidget> WidgetClass;


};
