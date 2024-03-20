// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"

#include "Engine/Engine.h"

#include "PlatformTrigger.h"
#include "Blueprint/UserWidget.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/MenuSystem/WBP_MainMenu.WBP_MainMenu_C'"));
	
	if (MenuBPClass.Class != NULL)
	{
		MenuClass = MenuBPClass.Class;
	}
	
}

void UPuzzlePlatformsGameInstance::Init()
{
	if (MenuClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found Class %s"), *MenuClass->GetName());
	}
	
}

void UPuzzlePlatformsGameInstance::LoadMenu()
{
	if (!MenuClass) return;

	UUserWidget* Menu = CreateWidget<UUserWidget>(this, MenuClass);
	if (!Menu) return;

	Menu->AddToViewport();

	// 플레이어 컨트롤러 받아오기
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!PlayerController) return;

	FInputModeUIOnly InputModeData;
	// 사용자 입력이 메뉴 위젯으로 집중되도록 설정
	InputModeData.SetWidgetToFocus(Menu->TakeWidget());
	// 마우스를 뷰포트에 잠그지 않도록 지정
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	// 위에서 만든 Data를 PlayerController에 적용하기
	PlayerController->SetInputMode(InputModeData);

	// 마우스 커서가 보이도록 설정
	PlayerController->bShowMouseCursor = true;
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
