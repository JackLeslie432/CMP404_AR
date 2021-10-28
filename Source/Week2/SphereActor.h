// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomActor.h"
#include "GameFramework/Actor.h"
#include "SphereActor.generated.h"

UCLASS()
class WEEK2_API ASphereActor : public ACustomActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASphereActor();

protected:
	

public:	
	virtual void Tick(float DeltaTime) override;


};
