// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RIM_WidgetActor_Title.generated.h"

UCLASS()
class SS_FINAL_API ARIM_WidgetActor_Title : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARIM_WidgetActor_Title();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	//타이틀 위젯 추가
	UPROPERTY(EditAnywhere)
	class UWidgetComponent* widget_Title;

public:
	//[위젯에서 버튼 클릭 했을 때 실행 될 함수]
	void PlayStart();



};
