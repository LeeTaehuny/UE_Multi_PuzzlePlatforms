// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatforms.h"

// Sets default values
AMovingPlatforms::AMovingPlatforms()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatforms::BeginPlay()
{
	Super::BeginPlay();

	// 서버에 있는 경우
	if (HasAuthority())
	{
		// 현재 액터를 서버에 복제하겠다는 의미
		SetReplicates(true);
		// 현재 액터의 움직임을 서버에 복제하겠다는 의미
		SetReplicateMovement(true);
	}

	// 시작 지점과 목표 지점 설정
	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
}

// Called every frame
void AMovingPlatforms::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		FVector Location = GetActorLocation();

		if ((Location - GlobalStartLocation).Size() > (GlobalTargetLocation - GlobalStartLocation).Size())
		{
			FVector Temp = GlobalTargetLocation;
			GlobalTargetLocation = GlobalStartLocation;
			GlobalStartLocation = Temp;
		}

		FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();

		Location += Direction * Speed * DeltaTime;
		SetActorLocation(Location);
	}
	
}

