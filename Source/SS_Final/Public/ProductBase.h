// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSVLoader.h"
#include "ProductBase.generated.h"


UCLASS()
class SS_FINAL_API AProductBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProductBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



public:

	// 메쉬 컴포넌트
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* compProductMesh;

	// 고스트 컴포넌트
	UPROPERTY(EditAnywhere)
	class AJS_ProductGhost* ghostActor;

	// 매니저 컴포넌트
	class AJS_ProductManager* productManager;

	// 플레이어
	UPROPERTY(EditAnywhere)
	class ACharacterBase* player;

	// 제품 판별 변수
	// 0일시 제품 베이스 1일시 라이트베이스
	int32 kindProduct = 0;

	// 제품 위젯 액터
	UPROPERTY(EditAnywhere)
	class AJS_WidgetActor* productWidget;
	UPROPERTY(EditAnywhere)
	FWidgetProductInfo info;

	// 제품 회전
	void RotateProduct();

	// 제품 구조체로 초기화
	void SetInit(FWidgetProductInfo value);
};
