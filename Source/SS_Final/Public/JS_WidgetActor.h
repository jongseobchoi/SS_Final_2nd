// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JS_InteractionComp.h"
#include "GameFramework/Actor.h"
#include "JS_WidgetActor.generated.h"


UCLASS()
class SS_FINAL_API AJS_WidgetActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJS_WidgetActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	class ACharacterBase* player;
	// 위젯 담을 컴포넌트
	UPROPERTY(EditAnywhere)
	class UWidgetComponent* compWidget;
	// 제품 위젯 서브클래스
	TSubclassOf<UUserWidget> productWidgetFactroy;
	// 바닥 위젯
	TSubclassOf<UUserWidget> floorWidgetFactroy;
	// 벽 위젯
	TSubclassOf<UUserWidget> wallWidgetFactroy;
	// 활성화 함수
	void SetActive(bool value);
	// 맞은 액터의 상태에 따른 보여줄 위젯 선택
	void SetWidgetType(EHitActorState value);
	// 맞은 액터 상태 변수 파싱용
	EHitActorState actorState;
};
