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

	// ��ǰ Ŭ���� ����
	UPROPERTY(EditAnywhere)
	class AProductBase* product;

	// ������ ��ġ�� ���͵�
	UPROPERTY(EditAnywhere)
	TArray<AActor*> outActors;

	// ������ ��ġ�� ���͵� �迭 (�����)
	UPROPERTY(EditAnywhere)
	TArray<AProductBase*> savedProductArr;

	// ������ ��ġ�� ���͵� �迭 (������)
	UPROPERTY(EditAnywhere)
	TArray<AProductBase*> currProductArr;

	// ��ǰ ���� �迭
	UPROPERTY(EditAnywhere)
	TArray<FObjectInfo> infoArr;


};
