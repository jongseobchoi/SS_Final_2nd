// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JS_FloorBase.h"
#include "JS_FloorLivingRoom.generated.h"

/**
 * 
 */
UCLASS()
class SS_FINAL_API AJS_FloorLivingRoom : public AJS_FloorBase
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AJS_FloorLivingRoom();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
