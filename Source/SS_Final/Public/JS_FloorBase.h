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
	// 바닥 메쉬 컴포넌트
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* compFloorMesh;

	// 바닥 재질 배열
	UPROPERTY(EditAnywhere)
	TArray<UMaterialInstance*> arrFloorMat;

	UPROPERTY(EditAnywhere)
	TArray<UMaterialInstance*> arrBathroomMat;


	// 바닥 머테리얼 변경 함수
	void ChangeFloorMat(int32 idx);

	// 바닥 재질 슬롯 갯수
	int32 matIdx;


///////////////////////////////////// 아래 정림 추가(텔레포트 이동을 위해)
public:
	UFUNCTION()
	void ComponentBeginOverlapMove(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	
};
