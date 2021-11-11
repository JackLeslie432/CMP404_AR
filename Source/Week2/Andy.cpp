// Fill out your copyright notice in the Description page of Project Settings.


#include "Andy.h"
#include "ARBlueprintLibrary.h"


// Sets default values
AAndy::AAndy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	//SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	//
	//StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	//StaticMeshComponent->AttachToComponent(SceneComponent, FAttachmentTransformRules::KeepRelativeTransform);
	//
	//static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/HelloAR/Assets/Meshes/Andy_Mesh.Andy_Mesh'"));
	//
	//static ConstructorHelpers::FObjectFinder<UMaterial> FoundMaterial(TEXT("Material'/Game/HelloAR/Assets/Materials/Andy_Mat_Default.Andy_Mat_Default'"));
	//if (FoundMaterial.Succeeded())
	//{
	//	StoredMaterial = FoundMaterial.Object;
	//}
	//
	//DynamicMaterialInst = UMaterialInstanceDynamic::Create(StoredMaterial, StaticMeshComponent);
	//
	//StaticMeshComponent->SetMaterial(0, DynamicMaterialInst);


}

// Called when the game starts or when spawned
void AAndy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAndy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAndy::AssignARPin(UARPin pin)
{
}

