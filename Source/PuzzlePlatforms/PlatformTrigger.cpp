// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformTrigger.h"
#include "Components/BoxComponent.h"
#include "PuzzlePlatforms/MovingPlatforms.h"

APlatformTrigger::APlatformTrigger()
{
 	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	if (!BoxComponent) return;

	RootComponent = BoxComponent;

	// 이벤트 설정
	// * 충돌 시작 / 종료 이벤트 등록
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &APlatformTrigger::OnOverlapBegin);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &APlatformTrigger::OnOverlapEnd);
}

void APlatformTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlatformTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlatformTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	for (AMovingPlatforms* Platform : PlatformsToTrigger)
	{
		Platform->AddActiveTrigger();
	}
}

void APlatformTrigger::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	for (AMovingPlatforms* Platform : PlatformsToTrigger)
	{
		Platform->RemoveActiveTrigger();
	}
}

