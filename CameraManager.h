#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraActor.h" // ACameraActor 사용을 위해 포함
#include "Components/AudioComponent.h" // UAudioComponent 사용을 위해 포함
#include "Sound/SoundCue.h" // USoundCue 사용을 위해 포함
#include "Blueprint/UserWidget.h"
#include "CameraManager.generated.h"

UCLASS()
class OBSERVATION2_API ACameraManager : public AActor
{
    GENERATED_BODY()

public:    
    // Sets default values for this actor's properties
    ACameraManager();

    UFUNCTION(BlueprintCallable, Category = "Camera")
    void SwitchToNextCamera();

    void SwitchToCamera(int32 CameraIndex);

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    float CurrentCamera();

    UPROPERTY(BlueprintReadOnly)
    int32 NowCameraIndex;



private:
    // 카메라 저장 배열
    UPROPERTY(EditAnywhere)
    TArray<AActor*> Cameras;

    int32 CurrentCameraIndex;

    UAudioComponent* SwitchCameraAudioComponent;

    UPROPERTY(EditAnywhere, Category = "Audio")
    USoundCue* SwitchCameraSoundCue; 

    UPROPERTY(EditAnyWhere, Category = "HiddenCamera")
    int32 WidgetCameraIndex;

    UPROPERTY(EditAnyWhere, Category = "HiddenCamera")
    TSubclassOf<UUserWidget> CameraWidgetClass;

    UUserWidget* CurrentWidgetInstance;

public:    
    // Called every frame
    virtual void Tick(float DeltaTime) override;
};
