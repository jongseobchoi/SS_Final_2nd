// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RIM_Widget_Title.generated.h"

/**
 * 
 */
UCLASS()
class SS_FINAL_API URIM_Widget_Title : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//[SetupPlayerInputComponent] 가상함수
	void SetupPlayerInputComponent(class UEnhancedInputComponent* PlayerInputComponent); //이거 없어도 될 거 같은데...?

public:
	//BeginPlay 와 같은 동작
	virtual void NativeConstruct() override;

public:
	//[블루프린트 위젯을 C++과 연결]
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_PlayStart; //시작 버튼


public:
	UPROPERTY()
	class ARIM_WidgetActor_Title* widgetActor_Title; //타이틀 위젯 액터


public:
	//[버튼 연결 함수]
	UFUNCTION()
	void Bind_btn_PlayStart();



};
