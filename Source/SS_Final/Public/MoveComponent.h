// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MoveComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SS_FINAL_API UMoveComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMoveComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	//[SetupPlayerInputComponent] �����Լ� �߰�
	void SetupPlayerInputComponent(class UEnhancedInputComponent* PlayerInputComponent);
	
public: 
	//[EnhancedInputComponent] �������Ʈ
	//Input Action. �޼� Ʈ���� ---> �ڸ���Ʈ �̵�
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class UInputAction* leftTrigger;
	//Input Action. �޼� ��ƽ ---> ȸ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UInputAction* leftStick;



public:
	//�÷��̾�
	class ACharacterBase* player;

	//World ĳ��
	class UWorld* currentWorld;

	//�̵� ������ �׸��� �ð� ����
	float lineTimeInterval = 0.05f; //���ʿ� �� ����

	//���� ��ġ���� �̵��� ��ġ ������...
	int32 lineTimeSegment = 50; //���ʿ� �� ����

	//�̵��� ��ġ
	TArray<FVector> lineLocation;

	//�Ŀ�
	UPROPERTY(EditAnywhere)
	float power = 300; //���ʿ� �� ����

	//���� �� ���δ�
	bool blsShowLine = false; //true �� �� �� �����Ӹ��� �׷���

	//�ڷ���Ʈ �̵��Ѵ�
	bool bIsTeleport = true;

	//�ڷ���Ʈ �̵� ������ ��ġ(����)
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//class AMoveLocation* position;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AJS_FloorBase* position;

	//�ڷ���Ʈ �� (����Ʈ�� ��Ƴ��� �׸�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ATeleportLocationRingActor> VFXTeleportRing;

	//�ڷ���Ʈ ��
	class ATeleportLocationRingActor* spawnedVFXTeleportRing;



public:
	//�̵� ����(�) �׸���
	void DrawMoveLine();
	//���� �̵�. ��� ��ǥ ����
	void Teleport();

	//�޼� Ʈ���� ---> �ڷ���Ʈ �̵�
	void leftTriggerShowLine();
	void leftTriggerHideLine();

	//�ڷ���Ʈ ī�޶� ���̵�
	void TeleportFade();

	//�޼� ��ƽ ---> �¿� ȸ��
	void LeftStickRotateAxis(const struct FInputActionValue& value);



};
