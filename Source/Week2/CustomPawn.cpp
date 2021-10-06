// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomPawn.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "ARBlueprintLibrary.h"

// Sets default values
ACustomPawn::ACustomPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Default Scene"));
	RootComponent = SceneComponent;

	CamComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CamComponent->SetupAttachment(RootComponent);

	cameraNotifyLoopTime = 4.0f;
}

void ACustomPawn::DisplayCameraInfo()
{
	FVector camLoc;
	FRotator camRot;

	UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraViewPoint(camLoc, camRot);

	FVector camOri = camRot.Vector();

	UKismetSystemLibrary::PrintString(this,FString::Printf(TEXT("Camera orientation: (%f, %f, %f)"), camOri.X, camOri.Y, camOri.Z), true, true, FLinearColor(0, 0.66, 1, 1), 5);

	SpawnActor(camOri);
}

// Called when the game starts or when spawned
void ACustomPawn::BeginPlay()
{
	Super::BeginPlay();
	UKismetSystemLibrary::PrintString(this, FString(TEXT("Hello world")), true, true, FLinearColor(0, 0.66, 1, 1), 5);

	UARSessionConfig* config = NewObject<UARSessionConfig>();
	UARBlueprintLibrary::StartARSession(config);

	GetWorldTimerManager().SetTimer(cameraTicker, this, &ACustomPawn::DisplayCameraInfo, cameraNotifyLoopTime, true, 0.0f);
}

// Called every frame
void ACustomPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACustomPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACustomPawn::SpawnActor(FVector dir)
{
	FActorSpawnParameters SpawnInfo;
	
	FRotator rot(0, 0, 0); 
	FVector loc(300, 1, 1); 
	ACustomActor* customActor = GetWorld()->SpawnActor<ACustomActor>(loc * dir, rot, SpawnInfo);
}

