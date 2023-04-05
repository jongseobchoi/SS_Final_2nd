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
	//씬(카메라, 컨트롤러 부모 용으로 만듬)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USceneComponent* compScene;

	//[카메라]
	//카메라
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* compCamera;
	//메시
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* meshCamera;

	//[왼손]
	//모션 컨트롤러
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMotionControllerComponent* compLeftCon;
	//메시
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* meshLeftHand;
	//[로그]
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTextRenderComponent* logLeft; //▶▶▶추후 삭제

	//[오른손]
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMotionControllerComponent* compRightCon;
	//메시
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* meshRightHand;
	//[로그]
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTextRenderComponent* logRight; //▶▶▶추후 삭제
	//[위젯포인터] 컨트롤러에 붙인 포인터(선)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetInteractionComponent* compWidgetPointer_right;


public:
	//Input Mapping Context. 블루프린트에서 만든 IMC_CharacterMapping
	UPROPERTY(EditAnywhere)
	class UInputMappingContext* CharacterMapping;

public:
	//[EnhancedInputComponent] 블루프린트
	//Input Action. 오른손 버튼 A ---> 오른손 위젯 열기. 닫기 ---> 왼손으로 옮김(삭제NO) ---> 위젯에서 가구 놓기
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class UInputAction* rightA;

	//Input Action. 왼손 버튼 X ---> 왼손 위젯 열기. 닫기
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class UInputAction* LeftX;

public:
	//[캐릭터에 액터컴포넌트 추가]
	//MoveComponent 를 캐릭터 에 추가
	UPROPERTY(EditAnywhere)
	class UMoveComponent* compMove;
	//WidgetPointerComponent 를 Player 에 추가. (위젯. 레이저 포인터 아님)
	UPROPERTY(EditAnywhere)
	class UWidgetPointerComponent* compWidget; //WidgetPointerComponent. 포인터가 작동하기 위해 필요

public:
	UPROPERTY()
	class AFinalGameModeBase* gameMode;

	UPROPERTY()
	class AWidgetActor_Righthand* righthandWidgetActor;
	

public:
	//[왼손에 왼손 위젯 붙임]
	UPROPERTY(EditAnywhere)
	class UWidgetComponent* compLefthandWidget;

	//[카메라에 가구 메인 위젯 붙임]
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UWidgetComponent* compAssetMainWidget;

	//[카메라에 세팅 위젯 붙임]
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetComponent* compSettingWidget;

	//[왼손에 주문금액 위젯 붙임]
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetComponent* compOrderWidget;

	//[카메라에 스샷 위젯 붙임]
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetComponent* compScreenShotWidget;

public:
	//왼손 버튼 X ---> 왼손 위젯 열기, 닫기 
	void SetLeftHandWidget();
	bool isWidgetOpen = false;

	//왼손 주문금액 위젯 노출
	void VisibleOrderWidget();

	//
	void VisibleHandMenuWidget();


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

public:
	
	// 현재 상태 변수
// 	UPROPERTY(EditAnywhere)
// 	EPlayerState currState

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Components")
	class UJS_InteractionComp* compInteraction;
	
	//Input Mapping Context. 블루프린트에서 만든 IMC_CharacterMapping (디버그용)
	UPROPERTY(EditAnywhere)
	class UInputMappingContext* DebugMapping;

	// 키 종류 선택(0:VR, 1:디버그)
	UPROPERTY(EditAnywhere, Category = "SelectInput")
	int32 selectInput = 0;

	// 걸어다니는 용도
	UPROPERTY(EditAnywhere, Category = "Inputs")
	class UInputAction* moveAction;

	// 카메라 회전
	UPROPERTY(EditAnywhere, Category = "Inputs")
	class UInputAction* cameraAction;

	// A버튼
	UPROPERTY(EditAnywhere, Category = "Inputs")
	class UInputAction* pressA;

	// B버튼
	UPROPERTY(EditAnywhere, Category = "Inputs")
	class UInputAction* pressB;

	// 1버튼
	UPROPERTY(EditAnywhere, Category = "Inputs")
	class UInputAction* press1;

	// 2버튼
	UPROPERTY(EditAnywhere, Category = "Inputs")
	class UInputAction* press2;

	// 3버튼
	UPROPERTY(EditAnywhere, Category = "Inputs")
	class UInputAction* press3;

	UPROPERTY(EditAnywhere, Category = "Inputs")
	class UInputAction* press4;
	
	UPROPERTY(EditAnywhere, Category = "Inputs")
	class UInputAction* press5;

	// 카메라 회전
	UPROPERTY(EditAnywhere, Category = "Inputs")
	class UInputAction* mouseXY;

	// 라인트레이스 발사 가능 여부 변수
	UPROPERTY(EditAnywhere, Category = "Inputs")
	bool bLine = false;

	// 디버깅용 캐릭터 움직이는 함수(WASD)
	void Move(const struct FInputActionValue& value);

	// A 버튼 트리거 (왼쪽 마우스 버튼)
	void TriggerA(const struct FInputActionValue& value);

	// A 버튼 스타트 (왼쪽 마우스 버튼)
	void StartedA();

	// A 버튼 릴리즈 (왼쪽 마우스 버튼)
	void ReleaseA();

	// B 버튼(오른쪽 마우스 버튼)
	void StartedB();

	// 1번버튼 (디버그용)
	void Started1();

	// 2번버튼 (디버그용)
	void Started2();

	// 3번버튼 (디버그용)
	void Started3();

	// 4번버튼 (디버그용)
	void Started4();

	// 5번버튼 (디버그용)
	void Started5();

	// 카메라(마우스 이동)
	void CameraRotate(const struct FInputActionValue& value);

	// 오른손 움직임(마우스 이동)
	void HandRotate(const struct FInputActionValue& value);

	// 현재 상태 변경 함수
	void ChangeState(EPlayerState value);
	void SpawnProduct();
	void IdleState();
	void OnDoorState();
	void WidgetState();
	void SelectedProductState();
	void CameraModeState();
	
	bool bButtonA = false;
	// 현재 상태 변수
	EPlayerState currState = EPlayerState::Idle;

	// 스태틱 매쉬 저장용 매니저
	UPROPERTY(EditAnywhere)
	class AJS_ProductManager* productManager;

	// 고스트 액터
	UPROPERTY(EditAnywhere)
	class AJS_ProductGhost* ghost;

	// 실제 스폰할 액터
	UPROPERTY(EditAnywhere)
	class AProductBase* product;

	UPROPERTY(EditAnywhere)
	class ALightBase* light;

	// 제품 위젯 위치값
	FVector smallWidgetLoc;

	// 스폰 파라미터
	FActorSpawnParameters spawnParams;

	// 현재 상태 FString
	FString stateName;

	// 고스트 변수
	class AJS_ProductGhost* productGhost;

	// 바닥 변수
	class AJS_FloorBase* floorBase;

	// 디버그용 라인트레이스 On/Off
	bool bDebugLine = false;


	
	// 디버그용 맞은 액터 판별 함수
	AActor* debugActor;
	
	// 맞은 액터 이름
	FString debugActorName;

	// 디버그용 맞은 액터 로케이션
	FVector debugActorLoc;

	// 스폰된 작은 위젯
	class AJS_WidgetActor* smallWidget;

	// 제품 위젯 활성화 변수
	bool bSmallWidget = false;
	// 위젯 컴포넌트 넣어두는 배열
	UPROPERTY(EditAnywhere)
	TArray<class UWidgetComponent*> arrWidgetComp;
	// 제품 위젯 소환 함수

	// 선택된 제품 담을 변수
	class AProductBase* selectedProduct;
	// 선택된 바닥 담을 변수
	class AJS_FloorBase* selectedFloor;
	// 선택된 벽 담을 변수
	class AJS_WallBase* selectedWall;

	// 낮/밤 컴포넌트 변수
	class ADirectionalLight* sunLight;

	// 낮/밤 판별 변수
	UPROPERTY(EditAnywhere)
	bool isNight = false;

	// 액터 상태 변수
	EHitActorState actorState;

	// 월드에 있는 탑뷰 카메라
	class AJS_CameraTopView* topViewCam;

	// 플레이어 컨트롤러
	APlayerController* playerCon;

	// 지금 오버랩된 문
	class AJS_DoorBase* currDoor;


	// 디버그용 라인트레이스 함수
	void DebugLineTrace(bool value);
	// 낮/밤 전환 함수
	UFUNCTION()
	void ChangeDayNight(bool value);
	// 스크린샷 함수
	void TakeScreenShot();
	// 제품 위젯 세팅 함수
	void SetSmallWidget(bool value);
	// 위젯 활성화 함수 0-hand, 1-main
	void SetWidgetActive(int32 compIdx, bool value);
	// 위젯 배열 초기화 함수
	void SetWidgetArr();
};
