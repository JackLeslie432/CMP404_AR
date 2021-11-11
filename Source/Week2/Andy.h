// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARPin.h"

#include "GameFramework/Actor.h"
#include "Andy.generated.h"

UCLASS()
class WEEK2_API AAndy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAndy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UARPin ARpin;

	UPROPERTY(Category = "myCategory", VisibleAnywhere, BlueprintReadWrite)
		USceneComponent* SceneComponent;

	UPROPERTY(Category = "myCategory", VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* StaticMeshComponent;

	UMaterial* StoredMaterial;
	UMaterialInstanceDynamic* DynamicMaterialInst;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void AssignARPin(UARPin pin);

};
