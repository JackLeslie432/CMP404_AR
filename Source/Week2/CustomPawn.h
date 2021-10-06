// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomActor.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include"TimerManager.h"
#include"Runtime/Engine/Classes/Kismet/GameplayStatics.h"
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

	FTimerHandle cameraTicker; 
	float cameraNotifyLoopTime;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void SpawnActor();

};
