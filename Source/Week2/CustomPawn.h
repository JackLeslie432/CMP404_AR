// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomActor.h"
#include "SphereActor.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "TimerManager.h"
#include "ARSessionConfig.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "CustomPawn.generated.h"

UCLASS()
class WEEK2_API ACustomPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACustomPawn();

	UPROPERTY(Category = "myCategory", VisibleAnywhere, BlueprintReadWrite)
		USceneComponent* SceneComponent;
	
	UPROPERTY(Category = "myCategory", VisibleAnywhere, BlueprintReadWrite)
		UCameraComponent* CamComponent;

	virtual void DisplayCameraInfo();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	bool WorldHitTest(FVector2D screenPos, FHitResult* hitResult);

	FTimerHandle cameraTicker; 
	float cameraNotifyLoopTime;

	bool cube = false;
	bool goghFound = false;
	bool earthFound = false;

	ACustomActor* GoghCube;
	ASphereActor* earthSphere;

	TArray<ACustomActor*> spawned;
	UARSessionConfig* ARconfig;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void SpawnActor(FVector dir);
	virtual void OnScreenTouch(const ETouchIndex::Type fingerIndex, const FVector screenPos);
};
