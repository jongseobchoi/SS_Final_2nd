// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JS_JSonObjectManager.generated.h"

USTRUCT()
struct FObjectInfo
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	int32 idx;

	UPROPERTY(EditAnywhere)
	class AProductBase* obj;

};

UCLASS()
class SS_FINAL_API AJS_JSonObjectManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AJS_JSonObjectManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SaveObject();
	void LoadObject();
	void DeleteAll();

	void CreateObject();
	void CreateObject(int32 type, FVector pos, float scale);

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProductBase> objectFactory;

	// 제품 클래스 변수
	UPROPERTY(EditAnywhere)
	class AProductBase* product;

	// 레벨에 배치된 액터들
	UPROPERTY(EditAnywhere)
	TArray<AActor*> outActors;

	// 레벨에 배치된 액터들 배열 (저장용)
	UPROPERTY(EditAnywhere)
	TArray<AProductBase*> savedProductArr;

	// 레벨에 배치된 액터들 배열 (삭제용)
	UPROPERTY(EditAnywhere)
	TArray<AProductBase*> currProductArr;

	// 제품 정보 배열
	UPROPERTY(EditAnywhere)
	TArray<FObjectInfo> infoArr;


};
