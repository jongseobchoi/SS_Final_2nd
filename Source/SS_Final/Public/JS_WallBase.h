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
	// �ٴ� �޽� ������Ʈ
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* compWallMesh;

	// �ٴ� ���� �迭
	UPROPERTY(EditAnywhere)
		TArray<UMaterialInstance*> arrWallMat;

	UPROPERTY(EditAnywhere)
		TArray<UMaterialInstance*> arrBathroomMat;
	

	// �ٴ� ���׸��� ���� �Լ�
	void ChangeWallMat(int32 idx);

	// �ٴ� ���� ���� ����
	int32 matIdx;



};
