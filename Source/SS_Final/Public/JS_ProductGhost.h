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

	// �÷��̾� ��������
	UPROPERTY()
	class ACharacterBase* player;

	// ��Ʈ ���� ������Ʈ �޽� ������Ʈ
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* compGhostMesh;

	// ��ǰ �Ŵ��� Ŭ����
	UPROPERTY(EditAnywhere)
	class AJS_ProductManager* productManager;

	// ���� ����ƽ �Ž�
	UPROPERTY(EditAnywhere)
	class UStaticMesh* currGhostMesh;

	// �Ǻ� ����
	bool canPlace = false;


	// �ʷϻ�(����) ���׸��� ����
	class UMaterialInstance* greenMat;

	//������(�Ұ���) ���׸��� ����
	class UMaterialInstance* redMat;

	int32 selectedWidgetIdx = 0;

	// ���� �� �ִ��� �Ǻ��Լ�
	void CanSofaPlace();

	// ���׸��� ���� ����
	int32 matIdx = 0;

	// �Ǻ��� ���� �� ����
	void CanSofaMat(bool value, int32 matCount);

	// Ȱ��ȭ ���� �Լ�
	void SetActive(bool value);
	
	// Ȱ��ȭ ���� ����
	bool bActive = false;

	// ���׸��� ���� �Լ�
	void ChangeSofaMat();

	// ���� ȸ�� �Լ�
	void RotateGhost();

	// CSV ���� ���� �޽� �ʱ�ȭ
	void SetInit(int32 value);
};
