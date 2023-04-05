// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JS_InteractionComp.generated.h"

UENUM(BlueprintType)
enum class EHitActorState : uint8
{
	Nothing,
	Floor,
	Wall,
	Product
};
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SS_FINAL_API UJS_InteractionComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UJS_InteractionComp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	// �÷��̾� ����
	class ACharacterBase* player;

	// ���� ������ ��ǰ ����
	class AProductBase* product;

	// Linetrace �߻� �Լ�
	void InteractionLineTrace();

	// ������ ����ü ����
	FActorSpawnParameters spawnParams;

	// ��ǰ �Ŵ���
	class AJS_ProductManager* productManager;

	// ����Ʈ���̽� �������� ��ġ (���� ���� �� ��ġ)
	FVector actorLoc;

	// ����Ʈ���̽� �������� Z�븻 ���� (���� ���� ����)
	FRotator spawnNormRot;

	// ��Ʈ�� ��ġ��
	FTransform ghostTrans;

	// ���� ����
	AActor* hitActor;

	// ���� ������ �̸�
	FString actorName;

	// ���� ���Ϳ� ���� ���� ��ȭ
	EHitActorState hitActorState = EHitActorState::Nothing;

	UClass* hitClass;

};
