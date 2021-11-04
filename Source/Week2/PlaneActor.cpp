// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaneActor.h"

// Sets default values
APlaneActor::APlaneActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'"));

	StaticMeshComponent->SetStaticMesh(MeshAsset.Object);
}

// Called when the game starts or when spawned
void APlaneActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlaneActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

