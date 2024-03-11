// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatforms.generated.h"

UCLASS()
class PUZZLEPLATFORMS_API AMovingPlatforms : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatforms();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void AddActiveTrigger();
	void RemoveActiveTrigger();

private:
	UPROPERTY(EditAnywhere, Category = "Option", meta = (AllowPrivateAccess = "true"))
	int32 Speed;

	UPROPERTY(EditAnywhere, Category = "Option", meta = (AllowPrivateAccess = "true"), meta = (MakeEditWidget = true))
	FVector TargetLocation;

	FVector GlobalTargetLocation;
	FVector GlobalStartLocation;

private:
	UPROPERTY(EditAnywhere, Category = "Trigger", meta = (AllowPrivateAccess = "true"))
	int32 ActiveTriggers = 1;
};
