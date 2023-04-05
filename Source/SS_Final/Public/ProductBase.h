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

	// �޽� ������Ʈ
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* compProductMesh;

	// ��Ʈ ������Ʈ
	UPROPERTY(EditAnywhere)
	class AJS_ProductGhost* ghostActor;

	// �Ŵ��� ������Ʈ
	class AJS_ProductManager* productManager;

	// �÷��̾�
	UPROPERTY(EditAnywhere)
	class ACharacterBase* player;

	// ��ǰ �Ǻ� ����
	// 0�Ͻ� ��ǰ ���̽� 1�Ͻ� ����Ʈ���̽�
	int32 kindProduct = 0;

	// ��ǰ ���� ����
	UPROPERTY(EditAnywhere)
	class AJS_WidgetActor* productWidget;
	UPROPERTY(EditAnywhere)
	FWidgetProductInfo info;

	// ��ǰ ȸ��
	void RotateProduct();

	// ��ǰ ����ü�� �ʱ�ȭ
	void SetInit(FWidgetProductInfo value);
};
