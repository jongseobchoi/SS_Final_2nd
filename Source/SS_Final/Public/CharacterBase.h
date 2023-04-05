// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JS_InteractionComp.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

 UENUM (BlueprintType)
 enum class EPlayerState : uint8
 {
 	Idle,
	OnDoor,
	SelectedProduct,
 	SpawnProduct,
 	OpenWidget,
	OpenProductWidget,
	CameraMode
 };

UCLASS()
class SS_FINAL_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:
	//[Scene]
	//��(ī�޶�, ��Ʈ�ѷ� �θ� ������ ����)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USceneComponent* compScene;

	//[ī�޶�]
	//ī�޶�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* compCamera;
	//�޽�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* meshCamera;

	//[�޼�]
	//��� ��Ʈ�ѷ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMotionControllerComponent* compLeftCon;
	//�޽�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* meshLeftHand;
	//[�α�]
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTextRenderComponent* logLeft; //���������� ����

	//[������]
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMotionControllerComponent* compRightCon;
	//�޽�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* meshRightHand;
	//[�α�]
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTextRenderComponent* logRight; //���������� ����
	//[����������] ��Ʈ�ѷ��� ���� ������(��)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetInteractionComponent* compWidgetPointer_right;


public:
	//Input Mapping Context. �������Ʈ���� ���� IMC_CharacterMapping
	UPROPERTY(EditAnywhere)
	class UInputMappingContext* CharacterMapping;

public:
	//[EnhancedInputComponent] �������Ʈ
	//Input Action. ������ ��ư A ---> ������ ���� ����. �ݱ� ---> �޼����� �ű�(����NO) ---> �������� ���� ����
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class UInputAction* rightA;

	//Input Action. �޼� ��ư X ---> �޼� ���� ����. �ݱ�
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class UInputAction* LeftX;

public:
	//[ĳ���Ϳ� ����������Ʈ �߰�]
	//MoveComponent �� ĳ���� �� �߰�
	UPROPERTY(EditAnywhere)
	class UMoveComponent* compMove;
	//WidgetPointerComponent �� Player �� �߰�. (����. ������ ������ �ƴ�)
	UPROPERTY(EditAnywhere)
	class UWidgetPointerComponent* compWidget; //WidgetPointerComponent. �����Ͱ� �۵��ϱ� ���� �ʿ�

public:
	UPROPERTY()
	class AFinalGameModeBase* gameMode;

	UPROPERTY()
	class AWidgetActor_Righthand* righthandWidgetActor;
	

public:
	//[�޼տ� �޼� ���� ����]
	UPROPERTY(EditAnywhere)
	class UWidgetComponent* compLefthandWidget;

	//[ī�޶� ���� ���� ���� ����]
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UWidgetComponent* compAssetMainWidget;

	//[ī�޶� ���� ���� ����]
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetComponent* compSettingWidget;

	//[�޼տ� �ֹ��ݾ� ���� ����]
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetComponent* compOrderWidget;

	//[ī�޶� ���� ���� ����]
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetComponent* compScreenShotWidget;

public:
	//�޼� ��ư X ---> �޼� ���� ����, �ݱ� 
	void SetLeftHandWidget();
	bool isWidgetOpen = false;

	//�޼� �ֹ��ݾ� ���� ����
	void VisibleOrderWidget();

	//
	void VisibleHandMenuWidget();


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

public:
	
	// ���� ���� ����
// 	UPROPERTY(EditAnywhere)
// 	EPlayerState currState

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Components")
	class UJS_InteractionComp* compInteraction;
	
	//Input Mapping Context. �������Ʈ���� ���� IMC_CharacterMapping (����׿�)
	UPROPERTY(EditAnywhere)
	class UInputMappingContext* DebugMapping;

	// Ű ���� ����(0:VR, 1:�����)
	UPROPERTY(EditAnywhere, Category = "SelectInput")
	int32 selectInput = 0;

	// �ɾ�ٴϴ� �뵵
	UPROPERTY(EditAnywhere, Category = "Inputs")
	class UInputAction* moveAction;

	// ī�޶� ȸ��
	UPROPERTY(EditAnywhere, Category = "Inputs")
	class UInputAction* cameraAction;

	// A��ư
	UPROPERTY(EditAnywhere, Category = "Inputs")
	class UInputAction* pressA;

	// B��ư
	UPROPERTY(EditAnywhere, Category = "Inputs")
	class UInputAction* pressB;

	// 1��ư
	UPROPERTY(EditAnywhere, Category = "Inputs")
	class UInputAction* press1;

	// 2��ư
	UPROPERTY(EditAnywhere, Category = "Inputs")
	class UInputAction* press2;

	// 3��ư
	UPROPERTY(EditAnywhere, Category = "Inputs")
	class UInputAction* press3;

	UPROPERTY(EditAnywhere, Category = "Inputs")
	class UInputAction* press4;
	
	UPROPERTY(EditAnywhere, Category = "Inputs")
	class UInputAction* press5;

	// ī�޶� ȸ��
	UPROPERTY(EditAnywhere, Category = "Inputs")
	class UInputAction* mouseXY;

	// ����Ʈ���̽� �߻� ���� ���� ����
	UPROPERTY(EditAnywhere, Category = "Inputs")
	bool bLine = false;

	// ������ ĳ���� �����̴� �Լ�(WASD)
	void Move(const struct FInputActionValue& value);

	// A ��ư Ʈ���� (���� ���콺 ��ư)
	void TriggerA(const struct FInputActionValue& value);

	// A ��ư ��ŸƮ (���� ���콺 ��ư)
	void StartedA();

	// A ��ư ������ (���� ���콺 ��ư)
	void ReleaseA();

	// B ��ư(������ ���콺 ��ư)
	void StartedB();

	// 1����ư (����׿�)
	void Started1();

	// 2����ư (����׿�)
	void Started2();

	// 3����ư (����׿�)
	void Started3();

	// 4����ư (����׿�)
	void Started4();

	// 5����ư (����׿�)
	void Started5();

	// ī�޶�(���콺 �̵�)
	void CameraRotate(const struct FInputActionValue& value);

	// ������ ������(���콺 �̵�)
	void HandRotate(const struct FInputActionValue& value);

	// ���� ���� ���� �Լ�
	void ChangeState(EPlayerState value);
	void SpawnProduct();
	void IdleState();
	void OnDoorState();
	void WidgetState();
	void SelectedProductState();
	void CameraModeState();
	
	bool bButtonA = false;
	// ���� ���� ����
	EPlayerState currState = EPlayerState::Idle;

	// ����ƽ �Ž� ����� �Ŵ���
	UPROPERTY(EditAnywhere)
	class AJS_ProductManager* productManager;

	// ��Ʈ ����
	UPROPERTY(EditAnywhere)
	class AJS_ProductGhost* ghost;

	// ���� ������ ����
	UPROPERTY(EditAnywhere)
	class AProductBase* product;

	UPROPERTY(EditAnywhere)
	class ALightBase* light;

	// ��ǰ ���� ��ġ��
	FVector smallWidgetLoc;

	// ���� �Ķ����
	FActorSpawnParameters spawnParams;

	// ���� ���� FString
	FString stateName;

	// ��Ʈ ����
	class AJS_ProductGhost* productGhost;

	// �ٴ� ����
	class AJS_FloorBase* floorBase;

	// ����׿� ����Ʈ���̽� On/Off
	bool bDebugLine = false;


	
	// ����׿� ���� ���� �Ǻ� �Լ�
	AActor* debugActor;
	
	// ���� ���� �̸�
	FString debugActorName;

	// ����׿� ���� ���� �����̼�
	FVector debugActorLoc;

	// ������ ���� ����
	class AJS_WidgetActor* smallWidget;

	// ��ǰ ���� Ȱ��ȭ ����
	bool bSmallWidget = false;
	// ���� ������Ʈ �־�δ� �迭
	UPROPERTY(EditAnywhere)
	TArray<class UWidgetComponent*> arrWidgetComp;
	// ��ǰ ���� ��ȯ �Լ�

	// ���õ� ��ǰ ���� ����
	class AProductBase* selectedProduct;
	// ���õ� �ٴ� ���� ����
	class AJS_FloorBase* selectedFloor;
	// ���õ� �� ���� ����
	class AJS_WallBase* selectedWall;

	// ��/�� ������Ʈ ����
	class ADirectionalLight* sunLight;

	// ��/�� �Ǻ� ����
	UPROPERTY(EditAnywhere)
	bool isNight = false;

	// ���� ���� ����
	EHitActorState actorState;

	// ���忡 �ִ� ž�� ī�޶�
	class AJS_CameraTopView* topViewCam;

	// �÷��̾� ��Ʈ�ѷ�
	APlayerController* playerCon;

	// ���� �������� ��
	class AJS_DoorBase* currDoor;


	// ����׿� ����Ʈ���̽� �Լ�
	void DebugLineTrace(bool value);
	// ��/�� ��ȯ �Լ�
	UFUNCTION()
	void ChangeDayNight(bool value);
	// ��ũ���� �Լ�
	void TakeScreenShot();
	// ��ǰ ���� ���� �Լ�
	void SetSmallWidget(bool value);
	// ���� Ȱ��ȭ �Լ� 0-hand, 1-main
	void SetWidgetActive(int32 compIdx, bool value);
	// ���� �迭 �ʱ�ȭ �Լ�
	void SetWidgetArr();
};
