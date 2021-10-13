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

bool ACustomPawn::WorldHitTest(FVector2D screenPos, FHitResult* hitResult)
{
	APlayerController* playerController = UGameplayStatics::GetPlayerController(this, 0);

	FVector worldPos,worldDir;
	bool deproctionSuccess = UGameplayStatics::DeprojectScreenToWorld(playerController, screenPos, worldPos, worldDir);
	
	FVector traceVector = worldDir * 1000.f;
	traceVector = worldPos + traceVector;

	bool traceSuccess = GetWorld()->LineTraceSingleByChannel(*hitResult, worldPos, traceVector, ECollisionChannel::ECC_WorldDynamic);

	return traceSuccess;
}

// Called every frame
void ACustomPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (int i = 0; i < spawned.Num();i++)
	{
		float dist = GetActorLocation().Dist(GetActorLocation(), spawned[i]->GetActorLocation());
		
		//UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("Dist: (%f)"), dist), true, true, FLinearColor(0, 0.66, 1, 1), 5);

		if (dist < 300)
		{
			spawned[i]->DynamicMaterialInst->SetVectorParameterValue(FName("CustomColor"), FLinearColor(1, 0, 0));
		}
		else
		{
			spawned[i]->DynamicMaterialInst->SetVectorParameterValue(FName("CustomColor"), FLinearColor(0, 1, 0));
		}
	}
}

// Called to bind functionality to input
void ACustomPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &ACustomPawn::OnScreenTouch);
}

void ACustomPawn::SpawnActor(FVector dir)
{
	FActorSpawnParameters SpawnInfo;
	
	FRotator rot(0, 0, 0);
	rot = FRotator(dir.Normalize());
	FVector loc(200, 200, 200); 

	ACustomActor* customActor;

	if (cube)
	{
		customActor = GetWorld()->SpawnActor<ACustomActor>(loc * dir.Normalize(), rot, SpawnInfo);
	}
	else
	{
		customActor = GetWorld()->SpawnActor<ASphereActor>(loc * dir.Normalize(), rot, SpawnInfo);		
	}

	spawned.Add(customActor);
	cube = !cube;
}

void ACustomPawn::OnScreenTouch(const ETouchIndex::Type fingerIndex, const FVector screenPos)
{
	FHitResult hitResult;

	if (WorldHitTest(FVector2D(screenPos), &hitResult))
	{
		UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("Touched "))+hitResult.Actor->GetName(), true, true, FLinearColor(0, 0.66, 1, 1), 5);
		
	}
	else
	{
		UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("Missed")), true, true, FLinearColor(0, 0.66, 1, 1), 5);
	}
}

