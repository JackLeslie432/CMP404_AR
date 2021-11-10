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
	//CamComponent->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UARSessionConfig> 
	ConfigAsset(TEXT("/Game/Images/CustomSessionConfig"));

	ARconfig = ConfigAsset.Object;

	cameraNotifyLoopTime = 4.0f;
}

void ACustomPawn::DisplayCameraInfo()
{
	FVector camLoc;
	FRotator camRot;

	UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraViewPoint(camLoc, camRot);

	FVector camOri = camRot.Vector();

	UKismetSystemLibrary::PrintString(this,FString::Printf(TEXT("Camera orientation: (%f, %f, %f)"), camOri.X, camOri.Y, camOri.Z), true, true, FLinearColor(0, 0.66, 1, 1), 5);

	//SpawnActor(camOri);
}

// Called when the game starts or when spawned
void ACustomPawn::BeginPlay()
{
	Super::BeginPlay();
	UKismetSystemLibrary::PrintString(this, FString(TEXT("Hello world")), true, true, FLinearColor(0, 0.66, 1, 1), 5);

	//UARSessionConfig* config = NewObject<UARSessionConfig>();
	//UARBlueprintLibrary::StartARSession(ARconfig);

	GetWorldTimerManager().SetTimer(cameraTicker, this, &ACustomPawn::DisplayCameraInfo, cameraNotifyLoopTime, true, 0.0f);
	GetWorldTimerManager().SetTimer(cameraTicker, this, &ACustomPawn::CheckPlane, 1, true, 0.0f);
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

	for (UARPlaneGeometry* plane : UARBlueprintLibrary::GetAllGeometriesByClass<UARPlaneGeometry>())
	{
		//plane->DebugDraw(this->GetWorld(), FLinearColor::Red, 1.5f, 1.0f);
	}

	// Change color on distance to object
	for (int i = 0; i < spawned.Num();i++)
	{
		float dist = GetActorLocation().Dist(GetActorLocation(), spawned[i]->GetActorLocation());

		if (dist < 100)
		{
			spawned[i]->DynamicMaterialInst->SetVectorParameterValue(FName("CustomColor"), FLinearColor(1, 0, 0));
		}
		else
		{
			spawned[i]->DynamicMaterialInst->SetVectorParameterValue(FName("CustomColor"), FLinearColor(0, 1, 0));
		}
	}

	// Getting images that are tracked
	auto trackedImages = UARBlueprintLibrary::GetAllTrackedImages();

	goghOnScreen = false;
	earthOnScreen = false;

	// loop all images tracked on screen
	for(int i = 0; i <trackedImages.Num(); i++)
	{
		if (trackedImages[i]->GetDetectedImage() && floatyCube == NULL)
		{			
			if (trackedImages[i]->GetDetectedImage()->GetFriendlyName().Equals("gogh")) // Check for van gogh and spawn in a cube when found
			{
				auto Tf = trackedImages[i]->GetLocalToTrackingTransform();
				goghOnScreen = trackedImages[i]->IsTracked();

				if (!goghFound)
				{
					FActorSpawnParameters SpawnInfo;

					FRotator rot(0, 0, 0);
					FVector start(0, 0, 0);

					Tf.SetScale3D(FVector(0.1, 0.1, 0.1));

					auto imageLoc = Tf.GetLocation();

					GoghCube = GetWorld()->SpawnActor<ACustomActor>(ACustomActor::StaticClass(), Tf, SpawnInfo);
					GoghCube->SetActorLocation(imageLoc);

					goghFound = true;					
				}
				else
				{
					GoghCube->SetActorLocation(Tf.GetLocation());
				}
			}
			else if (trackedImages[i]->GetDetectedImage()->GetFriendlyName().Equals("earth")) // Check for the earth and spawn in sphere when found
			{
				auto Tf = trackedImages[i]->GetLocalToTrackingTransform();
				earthOnScreen = trackedImages[i]->IsTracked();
				if (!earthFound)
				{
					FActorSpawnParameters SpawnInfo;

					FRotator rot(0, 0, 0);
					FVector start(0, 0, 0);

					Tf.SetScale3D(FVector(0.1, 0.1, 0.1));

					auto imageLoc = Tf.GetLocation();

					earthSphere = GetWorld()->SpawnActor<ASphereActor>(ASphereActor::StaticClass(), Tf, SpawnInfo);
					earthSphere->SetActorLocation(imageLoc);

					earthFound = true;
				}
				else
				{
					//earthSphere->SetActorLocation(Tf.GetLocation());
				}
			}

		}
	}

	// Spawn cube between images if found
	if (goghOnScreen && earthOnScreen && floatyCube == NULL)
	{
		auto Tf1 = earthSphere->GetStartPos();
		auto Tf2 = GoghCube->GetStartPos();

		earthSphere->Destroy();
		GoghCube->Destroy();

		earthFound = false;
		goghFound = false;

		UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("Destroyed Both")), true, true, FLinearColor(0, 0.66, 1, 1), 5);

		FActorSpawnParameters SpawnInfo;

		FRotator rot(0, 0, 0);
		floatyCube = GetWorld()->SpawnActor<ACustomActor>(ACustomActor::StaticClass(), Tf1, rot,SpawnInfo);

		floatyCube->SetActorLocation(Tf1);
		floatyCube->SetEndPos(Tf2);
		floatyCube->SetMove(true);
		floatyCube->SetActorScale3D(FVector(0.1, 0.1, 0.1));
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

		if (hitResult.Actor->GetName().Contains("PlaneActor"))
		{
			if (!bSelected)
			{
				APlaneActor* temp = Cast<APlaneActor>(hitResult.Actor);
				temp->DynamicMaterialInst->SetVectorParameterValue(FName("CustomColor"), FLinearColor(1, 0, 0, 1.f));
				
				temp = NULL;
				delete temp;
				
				bSelected = true;
			}
			else
			{
				//Spawn cube
				FActorSpawnParameters SpawnInfo;

				FRotator rot(0,0,0);
				FVector spawnPos = hitResult.ImpactPoint;
				spawnPos.Z+=10;

				spawned.Add(GetWorld()->SpawnActor<ACustomActor>(ACustomActor::StaticClass(),spawnPos ,rot, SpawnInfo));
				spawned[spawned.Num() - 1]->SetActorScale3D(FVector(0.1f, 0.1f, 0.1f));
			}
		}
		else
		{
			bSelected = false;
		}
	}
	else
	{
		UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("Missed at: (%f, %f)"), screenPos.X, screenPos.Y), true, true, FLinearColor(0, 0.66, 1, 1), 5);

		bSelected = false;

		if (groundPlane)
			groundPlane->Destroy();
		
		for (int i =0;i < spawned.Num();i++ )
		{
			spawned[i]->Destroy();
		}

		spawned.Empty();
	}
}

void ACustomPawn::CheckPlane()
{
	if (!bSelected)
	{
		//Viewport Size
		const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());

		//Viewport Center           
		const FVector2D  ViewportCenter = FVector2D(ViewportSize.X / 2, ViewportSize.Y / 2);

		auto traceResult = UARBlueprintLibrary::LineTraceTrackedObjects(ViewportCenter);

		UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("Looking for plane at:(%f, %f)"), ViewportCenter.X, ViewportCenter.Y), true, true, FLinearColor(0, 0.66, 1, 1), 5);


		for (int i = 0; i < traceResult.Num(); i++)
		{
			if (!Cast<UARPlaneGeometry>(traceResult[i].GetTrackedGeometry()))
			{
				UKismetSystemLibrary::PrintString(this, FString(TEXT("Plane Found")), true, true, FLinearColor(0, 0.66, 1, 1), 5);

				auto Tf = traceResult[i].GetTrackedGeometry()->GetLocalToWorldTransform();

				FActorSpawnParameters SpawnInfo;

				auto planeLoc = Tf.GetLocation();

				if (groundPlane)
					groundPlane->Destroy();

				groundPlane = GetWorld()->SpawnActor<APlaneActor>(APlaneActor::StaticClass(), Tf, SpawnInfo);
				groundPlane->SetActorLocation(planeLoc);

				groundPlane->DynamicMaterialInst->SetVectorParameterValue(FName("CustomColor"), FLinearColor(1, 0, 0, 0.5f));
			}
		}
	}
}

