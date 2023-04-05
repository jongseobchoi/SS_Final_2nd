// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JS_WallBase.generated.h"

UCLASS()
class SS_FINAL_API AJS_WallBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJS_WallBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



public:
	// ¹Ù´Ú ¸Þ½¬ ÄÄÆ÷³ÍÆ®
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* compWallMesh;

	// ¹Ù´Ú ÀçÁú ¹è¿­
	UPROPERTY(EditAnywhere)
		TArray<UMaterialInstance*> arrWallMat;

	UPROPERTY(EditAnywhere)
		TArray<UMaterialInstance*> arrBathroomMat;
	

	// ¹Ù´Ú ¸ÓÅ×¸®¾ó º¯°æ ÇÔ¼ö
	void ChangeWallMat(int32 idx);

	// ¹Ù´Ú ÀçÁú ½½·Ô °¹¼ö
	int32 matIdx;



};
