#include "ObservationPlayerCameraManager.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"


AObservationPlayerCameraManager::AObservationPlayerCameraManager(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{   
    
    PrimaryActorTick.bCanEverTick = true;

}

void AObservationPlayerCameraManager::SwitchToNextCamera()
{
    UE_LOG(LogTemp, Warning, TEXT("Attempting to switch to the next camera. Current index: %d"), CurrentCameraIndex);

    if (Cameras.Num() > 0 )
    {
        UE_LOG(LogTemp, Warning, TEXT("Number of cameras available: %d"), Cameras.Num());
        
        CurrentCameraIndex = (CurrentCameraIndex + 1) % Cameras.Num();
        UE_LOG(LogTemp, Warning, TEXT("Switching to camera at index: %d"), CurrentCameraIndex);
        

        // SOUND NOT WORKING
    if (CameraSwitchSound)
    {
        UGameplayStatics::PlaySound2D(this, CameraSwitchSound);
        UE_LOG(LogTemp, Warning, TEXT("Sound played for camera switch."));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("CameraSwitchSound is null, cannot play sound."));
    }


        
        SwitchToCamera(CurrentCameraIndex);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("No cameras available to switch."));
    }
}

void AObservationPlayerCameraManager::SwitchToPreviousCamera()
{
    UE_LOG(LogTemp, Warning, TEXT("이전 카메라로 전환 시도 중. 현재 인덱스: %d"), CurrentCameraIndex);

    if (Cameras.Num() > 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("사용 가능한 카메라 수: %d"), Cameras.Num());

        // 현재 인덱스를 이전 카메라로 업데이트합니다.
        CurrentCameraIndex = (CurrentCameraIndex - 1 + Cameras.Num()) % Cameras.Num();
        UE_LOG(LogTemp, Warning, TEXT("인덱스 %d의 카메라로 전환합니다."), CurrentCameraIndex);

        // SOUND NOT WORKING
    if (CameraSwitchSound)
    {
        UGameplayStatics::PlaySound2D(this, CameraSwitchSound);
        UE_LOG(LogTemp, Warning, TEXT("Sound played for camera switch."));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("CameraSwitchSound is null, cannot play sound."));
    }

        // 카메라 전환
        SwitchToCamera(CurrentCameraIndex);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("전환할 수 있는 카메라가 없습니다."));
    }
}


void AObservationPlayerCameraManager::SwitchToCamera(int32 CameraIndex)
{
    UE_LOG(LogTemp, Warning, TEXT("Attempting to switch to camera at index: %d"), CameraIndex);
    
    if (Cameras.IsValidIndex(CameraIndex))
    {
        ACameraActor* NewCamera = Cast<ACameraActor>(Cameras[CameraIndex]);
        if (NewCamera)
        {
            UE_LOG(LogTemp, Warning, TEXT("Successfully cast to ACameraActor: %s"), *NewCamera->GetName());
            
            // Camera switching with a blend time
            SetViewTarget(NewCamera);
            AActor* NewViewTarget = this->GetViewTarget();

            // Check if the camera switch was successful
            if(NewViewTarget == NewCamera)
            {
                UE_LOG(LogTemp, Warning, TEXT("Successfully switched to camera: %s"), *NewCamera->GetName());
                
                // Update SceneCaptureComponent2D if it exists
                USceneCaptureComponent2D* CaptureComponent = NewCamera->FindComponentByClass<USceneCaptureComponent2D>();
                if (CaptureComponent)
                {
                    CaptureComponent->CaptureScene();
                    UE_LOG(LogTemp, Warning, TEXT("Updated SceneCaptureComponent2D for camera: %s"), *NewCamera->GetName());
                }
                else
                {
                    UE_LOG(LogTemp, Warning, TEXT("No SceneCaptureComponent2D found for camera: %s"), *NewCamera->GetName());
                }

                // Add on-screen debug message
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Switched to camera: %s"), *NewCamera->GetName()));

                // TODO: Add logic here to check if the render target has been updated
                // This might involve checking a specific property of your render target or material
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Failed to set new view target. Current view target: %s"), *NewViewTarget->GetName());
            }
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to cast to ACameraActor for index: %d"), CameraIndex);
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid CameraIndex: %d"), CameraIndex);
    }

    IsCameraSwitched = true;
}

void AObservationPlayerCameraManager::BeginPlay()
{
    Super::BeginPlay();

    IsCameraSwitched = false;

    PlayerController = GetOwningPlayerController();
    if (!PlayerController)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to get PlayerController"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Successfully obtained PlayerController: %s"), *PlayerController->GetName());
    }

    // 모든 ACameraActor를 찾아서 Cameras 배열에 추가
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), Cameras);
    
    if (Cameras.Num() > 0)
    {
        CurrentCameraIndex = 0;
        UE_LOG(LogTemp, Warning, TEXT("Found %d cameras"), Cameras.Num());

        // 각 카메라의 정보를 로그로 출력
        for (int32 i = 0; i < Cameras.Num(); ++i)
        {
            ACameraActor* Camera = Cast<ACameraActor>(Cameras[i]);
            if (Camera)
            {
                FVector Location = Camera->GetActorLocation();
                FRotator Rotation = Camera->GetActorRotation();
                UE_LOG(LogTemp, Warning, TEXT("Camera %d: Name=%s, Location=(X=%.2f, Y=%.2f, Z=%.2f), Rotation=(Pitch=%.2f, Yaw=%.2f, Roll=%.2f)"),
                    i, *Camera->GetName(), Location.X, Location.Y, Location.Z, Rotation.Pitch, Rotation.Yaw, Rotation.Roll);
            }
            
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Camera %d: Invalid camera actor"), i);
            }
        }

        
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("No cameras found"));
    }
}

float AObservationPlayerCameraManager::CurrentCamera()
{
    return CurrentCameraIndex;
}



void AObservationPlayerCameraManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // 매 프레임마다 로그를 출력하면 너무 많은 정보가 생성되므로, 일정 간격으로 로그를 출력합니다.
    static float TimeSinceLastLog = 0.0f;
    TimeSinceLastLog += DeltaTime;

    if (TimeSinceLastLog >= 1.0f)  // 1초마다 로그 출력
    {
        if (Cameras.IsValidIndex(CurrentCameraIndex))
        {
            AActor* CurrentCamera = Cameras[CurrentCameraIndex];
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Current Camera Index: %d (Invalid)"), CurrentCameraIndex);
        }

        TimeSinceLastLog = 0.0f;
    }

}

