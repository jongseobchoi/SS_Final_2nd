// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FurnitureBase.h"
#include "JS_SofaBase.generated.h"

/**
 * 
 */
UCLASS()
class SS_FINAL_API AJS_SofaBase : public AFurnitureBase
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AJS_SofaBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// 메쉬 컴포넌트
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* compSofaMesh;

	// 프로덕트 클래스
	class AProductBase* product;

	// 가구 클래스
	class AFurnitureBase* furniture;


	// Sofa 회전
	void RotateSofa();
	
};

