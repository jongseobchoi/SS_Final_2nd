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


	// �޽� ������Ʈ
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* compSofaMesh;

	// ���δ�Ʈ Ŭ����
	class AProductBase* product;

	// ���� Ŭ����
	class AFurnitureBase* furniture;


	// Sofa ȸ��
	void RotateSofa();
	
};

