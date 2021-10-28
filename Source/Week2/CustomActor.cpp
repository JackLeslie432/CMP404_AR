// Fill out your copyright notice in the Description page of Project Settings.
#include "CustomActor.h"

// Sets default values
ACustomActor::ACustomActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));	

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComponent->AttachToComponent(SceneComponent, FAttachmentTransformRules::KeepRelativeTransform);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'")); 

	static ConstructorHelpers::FObjectFinder<UMaterial> FoundMaterial(TEXT("/Game/HandheldARBP/Materials/M_BackgroundFade"));
	if (FoundMaterial.Succeeded())
	{
		StoredMaterial = FoundMaterial.Object;
	}
	DynamicMaterialInst = UMaterialInstanceDynamic::Create(StoredMaterial, StaticMeshComponent);
	
	StaticMeshComponent->SetMaterial(0, DynamicMaterialInst);

	StaticMeshComponent->SetStaticMesh(MeshAsset.Object);
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

	//m_moving.M[3][0] = 0;// this is the calculated X from the previous lab
	//m_moving.M[3][1] = y * 100;
	//m_moving.M[3][2] = x * 100;

	FMatrix m_final = m_moving * m_init ;

	//SetActorTransform(FTransform(m_final));
}

void ACustomActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	startPos = GetActorLocation();
}

