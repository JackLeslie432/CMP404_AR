// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CustomActor.generated.h"

UCLASS()
class WEEK2_API ACustomActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACustomActor();

	UPROPERTY(Category = "myCategory", VisibleAnywhere, BlueprintReadWrite)
		USceneComponent* SceneComponent;
	
	UPROPERTY(Category = "myCategory", VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* StaticMeshComponent;

	UMaterial* StoredMaterial;
	UMaterialInstanceDynamic* DynamicMaterialInst;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

	float time;
	float lerpAmount = 0.01f;
	float lerpTimer = 0.f;
	FVector startPos;
	FVector endPos;

	bool bMove = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetMove(bool inMove) { bMove = inMove; };
	void SetEndPos(FVector inEnd) {endPos = inEnd; };

	FVector GetStartPos() { return startPos; };

};
