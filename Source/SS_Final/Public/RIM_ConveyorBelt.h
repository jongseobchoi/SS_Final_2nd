// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RIM_ConveyorBelt.generated.h"

UCLASS()
class SS_FINAL_API ARIM_ConveyorBelt : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARIM_ConveyorBelt();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* compMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* compBox;


	UPROPERTY(EditAnywhere)
	float currentMoveSpeed = 200;

	UPROPERTY(EditAnywhere)
	class UArrowComponent* compArrow;

public:
	UFUNCTION()
	void Activity();

	bool isStop = false;

};
