// Fill out your copyright notice in the Description page of Project Settings.


#include "HiddenCamera.h"
#include "Camera/CameraActor.h"


AHiddenCamera::AHiddenCamera()
{


    bIsVisible = false;

}

void AHiddenCamera::BeginPlay()
{
    Super::BeginPlay();

    if(CameraClass)
    {
        CameraActor = GetWorld()->SpawnActor<ACameraActor>(CameraClass);

        if(CameraActor)
        {
            UE_LOG(LogTemp, Warning, TEXT("CameraActor successfully created."));
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to create CameraActor."));
        }
    }   
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("CameraClass is null."));
    }
}

void AHiddenCamera::ShowHiddenCamera()
{
    bIsVisible = true;


}
