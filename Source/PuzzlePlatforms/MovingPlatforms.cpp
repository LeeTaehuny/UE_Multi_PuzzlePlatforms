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

	// ������ �ִ� ���
	if (HasAuthority())
	{
		// ���� ���͸� ������ �����ϰڴٴ� �ǹ�
		SetReplicates(true);
		// ���� ������ �������� ������ �����ϰڴٴ� �ǹ�
		SetReplicateMovement(true);
	}

	// ���� ������ ��ǥ ���� ����
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

