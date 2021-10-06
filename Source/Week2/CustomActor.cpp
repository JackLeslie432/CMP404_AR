// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomActor.h"

// Sets default values
ACustomActor::ACustomActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));	

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'")); 
	StaticMeshComponent->SetStaticMesh(MeshAsset.Object);

	StaticMeshComponent->AttachToComponent(SceneComponent, FAttachmentTransformRules::KeepRelativeTransform);
	SetRootComponent(SceneComponent);
}

// Called when the game starts or when spawned
void ACustomActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACustomActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	time += DeltaTime;

	FVector pos = GetActorLocation();
	
	float scale = 2 / (3 - cos(2 * time)); 
	float x = scale * cos(time); 
	float y = scale * sin(2 * time) / 2;

	pos.X += x;
	pos.Y += y;	

	SetActorLocation(pos);
}

