#include "CameraPlayerController.h"
#include "CameraManager.h"
#include "GameFramework/PlayerController.h"
#include "ObservationPlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"




ACameraPlayerController::ACameraPlayerController()
{ 
	PlayerCameraManagerClass = AObservationPlayerCameraManager::StaticClass();
}


void ACameraPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    // Bind actions
    InputComponent->BindAction("SwitchCamera1", IE_Pressed, this, &ACameraPlayerController::SwitchToNextCamera);
    InputComponent->BindAction("SwitchCamera2", IE_Pressed, this, &ACameraPlayerController::SwitchToPreviousCamera);

    // Find CameraManager from PlayerController
    CameraManager = Cast<AObservationPlayerCameraManager>(PlayerCameraManager);
    if (CameraManager)
    {
        UE_LOG(LogTemp, Warning, TEXT("CameraManager found %s"), *CameraManager->GetName());
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("CameraManager not found or cast failed"));
    }
}


void ACameraPlayerController::UpdateTimer()
{
    ElapsedTime += 1.0f; // 초 단위로 증가

    // 시간을 HH:MM:SS 형식으로 변환
    int32 ElapsedTimeInt = FMath::FloorToInt(ElapsedTime);
    //int32 Hours = ElapsedTimeInt / 3600;
    int32 Minutes = (ElapsedTimeInt / 60) % 60;
    int32 Seconds = ElapsedTimeInt % 60;

    // 타이머 텍스트 업데이트
    TimerText = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);
}

float ACameraPlayerController::CurrentCamera()
{
	return CameraManager->CurrentCamera();
}

float ACameraPlayerController::GetElapsedTime() const
{
    return ElapsedTime;
}

void ACameraPlayerController::SwitchToPreviousCamera()
{
    if(CameraManager)
    {
        CameraManager->SwitchToPreviousCamera();
        UE_LOG(LogTemp, Warning, TEXT("Switched Camera"));
    }
}



void ACameraPlayerController::SwitchToNextCamera()
{
	if (CameraManager)
	{
		CameraManager->SwitchToNextCamera();
        UE_LOG(LogTemp, Warning, TEXT("Switched Camera"));
	}

}

void ACameraPlayerController::BeginPlay()
{
    Super::BeginPlay();

    // 타이머 초기화
    ElapsedTime = 0.0f;

    // 타이머 이벤트 설정 (매 1초마다 UpdateTimer 함수 호출)
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ACameraPlayerController::UpdateTimer, 1.0f, true, 2.5f);
}

