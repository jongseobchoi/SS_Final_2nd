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
	//[SetupPlayerInputComponent] 가상함수 추가
	void SetupPlayerInputComponent(class UEnhancedInputComponent* PlayerInputComponent);
	
public: 
	//[EnhancedInputComponent] 블루프린트
	//Input Action. 왼손 트리거 ---> 텔리포트 이동
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class UInputAction* leftTrigger;
	//Input Action. 왼손 스틱 ---> 회전
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UInputAction* leftStick;



public:
	//플레이어
	class ACharacterBase* player;

	//World 캐싱
	class UWorld* currentWorld;

	//이동 라인을 그리는 시간 간격
	float lineTimeInterval = 0.05f; //▶필요 시 조정

	//현재 위치에서 이동할 위치 사이의...
	int32 lineTimeSegment = 50; //▶필요 시 조정

	//이동할 위치
	TArray<FVector> lineLocation;

	//파워
	UPROPERTY(EditAnywhere)
	float power = 300; //▶필요 시 조정

	//라인 안 보인다
	bool blsShowLine = false; //true 일 때 매 프레임마다 그려라

	//텔레포트 이동한다
	bool bIsTeleport = true;

	//텔레포트 이동 가능한 위치(영역)
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//class AMoveLocation* position;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AJS_FloorBase* position;

	//텔레포트 링 (이펙트를 담아놓는 그릇)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ATeleportLocationRingActor> VFXTeleportRing;

	//텔레포트 링
	class ATeleportLocationRingActor* spawnedVFXTeleportRing;



public:
	//이동 라인(곡선) 그리기
	void DrawMoveLine();
	//순간 이동. 즉시 좌표 변경
	void Teleport();

	//왼손 트리거 ---> 텔레포트 이동
	void leftTriggerShowLine();
	void leftTriggerHideLine();

	//텔레포트 카메라 페이드
	void TeleportFade();

	//왼손 스틱 ---> 좌우 회전
	void LeftStickRotateAxis(const struct FInputActionValue& value);



};
