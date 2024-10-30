// Copyright Epic Games, Inc. All Rights Reserved.

#include "OBSERVATION2GameMode.h"
#include "OBSERVATION2Character.h"
#include "CameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"


AOBSERVATION2GameMode::AOBSERVATION2GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	PlayerControllerClass = ACameraPlayerController::StaticClass();
}


void AOBSERVATION2GameMode::BeginPlay()
{
	Super::BeginPlay();

	// Get CameraManager from the World and assign it to CameraManagerRef
	CameraManagerRef = Cast<ACameraManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ACameraManager::StaticClass()));

	// Alternatively, if CameraManager is derived from GameMode:
	// CameraManagerRef = GetWorld()->GetAuthGameMode<ACameraManager>();
}