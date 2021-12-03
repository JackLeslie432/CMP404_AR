// Fill out your copyright notice in the Description page of Project Settings.


#include "AndyActor.h"

// Sets default values
AAndyActor::AAndyActor()
{

}

// Called when the game starts or when spawned
void AAndyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAndyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAndyActor::AssignARPin(UARPin pin)
{
	ARpin = pin;
}

