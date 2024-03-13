// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"

#include "Engine/Engine.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance()
{
	UE_LOG(LogTemp, Warning, TEXT("Start Construct"));
}

void UPuzzlePlatformsGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("Start Init"));
}

void UPuzzlePlatformsGameInstance::Host()
{
	// AddOnScreenDebugMessage() 함수를 사용해 화면에 로그 띄우기

	UEngine* Engine = GetEngine();
	if (!Engine) return;

	Engine->AddOnScreenDebugMessage(0, 1.5f, FColor::Green, TEXT("Hosting"));

	UWorld* World = GetWorld();

	if (!World) return;

	World->ServerTravel("/Game/ThirdPerson/Maps/ThirdPersonMap?listen");
}

void UPuzzlePlatformsGameInstance::Join(const FString& Address)
{
	// AddOnScreenDebugMessage() 함수를 사용해 화면에 로그 띄우기

	UEngine* Engine = GetEngine();
	if (!Engine) return;

	Engine->AddOnScreenDebugMessage(0, 1.5f, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));

	// 플레이어 컨트롤러 받아오기
	APlayerController* PlayerController = GetFirstLocalPlayerController();

	if (!PlayerController) return;

	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}
