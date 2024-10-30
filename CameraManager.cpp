// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraManager.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"

#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"


// Sets default values
ACameraManager::ACameraManager()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    SwitchCameraAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("SwitchCameraAudioComponent"));
    SwitchCameraAudioComponent->SetupAttachment(RootComponent);

    CameraWidgetClass = nullptr;
    WidgetCameraIndex = 0;
}

void ACameraManager::SwitchToNextCamera()
{
	if(Cameras.Num() > 0 )
	{
		if(Cameras.Num() > 0)
		{
			CurrentCameraIndex = (CurrentCameraIndex + 1) % Cameras.Num();
			            // 사운드 재생
            if (SwitchCameraSoundCue)
            {
                SwitchCameraAudioComponent->SetSound(SwitchCameraSoundCue);
                SwitchCameraAudioComponent->Play();

                UE_LOG(LogTemp, Warning, TEXT("Playing camera switch sound"));
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("SwitchCameraSoundCue is not set"));
                return;
            }

            SwitchToCamera(CurrentCameraIndex);
		}
	}
}


void ACameraManager::SwitchToCamera(int32 CameraIndex)
{
    // Check if the CameraIndex is valid
    if (Cameras.IsValidIndex(CameraIndex))
    {
        ACameraActor* NewCamera = Cast<ACameraActor>(Cameras[CameraIndex]);
        if (NewCamera)
        {
            APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
            if (!PlayerController)
            {
                UE_LOG(LogTemp, Error, TEXT("Failed to get PlayerController"));
                return; // 에러 발생 시 함수 종료
            }

            // Log the current and new camera information
            UE_LOG(LogTemp, Warning, TEXT("Switching to camera index: %d"), CameraIndex);
            UE_LOG(LogTemp, Warning, TEXT("Current Camera: %s"), *PlayerController->GetViewTarget()->GetName());
            UE_LOG(LogTemp, Warning, TEXT("New Camera: %s"), *NewCamera->GetName());

            // Camera switching with a blend time
            PlayerController->SetViewTargetWithBlend(NewCamera, 0.1f);
            
            // Update NowCameraIndex to the current camera index
            NowCameraIndex = CameraIndex;  // Update the current camera index

            AActor* NewViewTarget = PlayerController->GetViewTarget();

            if (NewViewTarget != NewCamera)
            {
                UE_LOG(LogTemp, Error, TEXT("Failed to set new view target"));
            }

            // Log success message
            UE_LOG(LogTemp, Warning, TEXT("Successfully switched to camera: %s"), *NewCamera->GetName());
        }
        else
        {
            // Log error if casting failed
            UE_LOG(LogTemp, Error, TEXT("Failed to cast to ACameraActor for index: %d"), CameraIndex);
        }
    }
    else
    {
        // Log error if CameraIndex is invalid
        UE_LOG(LogTemp, Error, TEXT("Invalid CameraIndex: %d"), CameraIndex);
    }
}





// Called when the game starts or when spawned
void ACameraManager::BeginPlay()
{
    Super::BeginPlay();
    
    // 모든 ACameraActor를 찾아서 Cameras 배열에 추가
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), Cameras);

    if (Cameras.Num() > 0)
    {
        CurrentCameraIndex = 0;
        NowCameraIndex = 0; 
        UE_LOG(LogTemp, Warning, TEXT("Current Camera Index: %d"), CurrentCameraIndex);
        
        UE_LOG(LogTemp, Warning, TEXT("Found %d cameras"), Cameras.Num());

        // 시작할 때 첫 번째 카메라로 전환
        SwitchToCamera(CurrentCameraIndex);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("No cameras found"));
    }
}


float ACameraManager::CurrentCamera()
{
    return CurrentCameraIndex;
}


// Called every frame
void ACameraManager::Tick(float DeltaTime)
{

}


