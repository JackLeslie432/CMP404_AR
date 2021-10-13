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
