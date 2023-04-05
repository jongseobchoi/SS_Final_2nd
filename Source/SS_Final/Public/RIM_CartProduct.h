// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSVLoader.h"
#include "RIM_CartProduct.generated.h"

UCLASS()
class SS_FINAL_API ARIM_CartProduct : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARIM_CartProduct();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* compMesh;
	UPROPERTY(EditAnywhere)
	class UBoxComponent* compBox;

// 	UFUNCTION()
// 	void SetInit(mesh); //� mesh �� ���� �𸣴ϱ�...
	UFUNCTION()
	void SetInit(FWidgetProductInfo info); 

public:
	//�޽ÿ� ���� ����
	UPROPERTY(EditAnywhere)
	class UWidgetComponent* compProductInfo;

	UPROPERTY(EditAnywhere)
	FWidgetProductInfo productInfo;

public:
	//void TotalPriceCount();

};
