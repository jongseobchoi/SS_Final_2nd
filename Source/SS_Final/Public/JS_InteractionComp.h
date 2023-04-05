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
	// 플레이어 변수
	class ACharacterBase* player;

	// 실제 스폰할 제품 변수
	class AProductBase* product;

	// Linetrace 발사 함수
	void InteractionLineTrace();

	// 스폰용 구조체 변수
	FActorSpawnParameters spawnParams;

	// 제품 매니저
	class AJS_ProductManager* productManager;

	// 라인트레이스 맞은곳의 위치 (가구 스폰 할 위치)
	FVector actorLoc;

	// 라인트레이스 맞은곳의 Z노말 방향 (가구 세울 방향)
	FRotator spawnNormRot;

	// 고스트의 위치값
	FTransform ghostTrans;

	// 맞은 액터
	AActor* hitActor;

	// 맞은 액터의 이름
	FString actorName;

	// 맞은 액터에 따른 상태 변화
	EHitActorState hitActorState = EHitActorState::Nothing;

	UClass* hitClass;

};
