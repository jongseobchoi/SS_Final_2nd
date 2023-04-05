// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JS_ProductGhost.generated.h"

UCLASS()
class SS_FINAL_API AJS_ProductGhost : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJS_ProductGhost();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	// 플레이어 가져오기
	UPROPERTY()
	class ACharacterBase* player;

	// 고스트 액터 컴포넌트 메쉬 컴포넌트
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* compGhostMesh;

	// 제품 매니저 클래스
	UPROPERTY(EditAnywhere)
	class AJS_ProductManager* productManager;

	// 현재 스태틱 매쉬
	UPROPERTY(EditAnywhere)
	class UStaticMesh* currGhostMesh;

	// 판별 변수
	bool canPlace = false;


	// 초록색(가능) 머테리얼 변수
	class UMaterialInstance* greenMat;

	//빨간색(불가능) 머테리얼 변수
	class UMaterialInstance* redMat;

	int32 selectedWidgetIdx = 0;

	// 놓을 수 있는지 판별함수
	void CanSofaPlace();

	// 머테리얼 슬롯 개수
	int32 matIdx = 0;

	// 판별에 따른 색 변경
	void CanSofaMat(bool value, int32 matCount);

	// 활성화 상태 함수
	void SetActive(bool value);
	
	// 활성화 결정 변수
	bool bActive = false;

	// 머테리얼 변경 함수
	void ChangeSofaMat();

	// 가구 회전 함수
	void RotateGhost();

	// CSV 값에 따른 메쉬 초기화
	void SetInit(int32 value);
};
