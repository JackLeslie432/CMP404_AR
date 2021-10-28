// Fill out your copyright notice in the Description page of Project Settings.


#include "SphereActor.h"

// Sets default values
ASphereActor::ASphereActor() : ACustomActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;	

	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));

	StaticMeshComponent->SetStaticMesh(MeshAsset.Object);

}

void ASphereActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	time += DeltaTime;

	FMatrix m_init;

	m_init = FMatrix::Identity;
	m_init.M[3][0] = startPos.X;
	m_init.M[3][1] = startPos.Y;
	m_init.M[3][2] = startPos.Z;

	//FVector pos = GetActorLocation();

	float scale = 2 / (3 - cos(2 * time));
	float x = scale * cos(time);
	float y = scale * sin(2 * time) / 2;

	//pos.X = y*100;
	//pos.Y = x*100;

	FMatrix m_moving = FMatrix::Identity;

	m_moving.M[3][0] = 0;// this is the calculated X from the previous lab
	m_moving.M[3][1] = y * 100;
	m_moving.M[3][2] = x * 100;

	FMatrix m_final = m_moving * m_init;

	FTransform temp(m_final);

	SetActorLocation(temp.GetLocation());
}