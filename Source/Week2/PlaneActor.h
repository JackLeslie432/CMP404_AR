// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomActor.h"
#include "GameFramework/Actor.h"
#include "PlaneActor.generated.h"

UCLASS()
class WEEK2_API APlaneActor : public ACustomActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlaneActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
