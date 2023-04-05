// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JS_FloorBase.generated.h"

UCLASS()
class SS_FINAL_API AJS_FloorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJS_FloorBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	// �ٴ� �޽� ������Ʈ
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* compFloorMesh;

	// �ٴ� ���� �迭
	UPROPERTY(EditAnywhere)
	TArray<UMaterialInstance*> arrFloorMat;

	UPROPERTY(EditAnywhere)
	TArray<UMaterialInstance*> arrBathroomMat;


	// �ٴ� ���׸��� ���� �Լ�
	void ChangeFloorMat(int32 idx);

	// �ٴ� ���� ���� ����
	int32 matIdx;


///////////////////////////////////// �Ʒ� ���� �߰�(�ڷ���Ʈ �̵��� ����)
public:
	UFUNCTION()
	void ComponentBeginOverlapMove(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	
};
