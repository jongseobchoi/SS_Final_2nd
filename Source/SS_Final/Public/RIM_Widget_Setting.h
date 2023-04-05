// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RIM_Widget_Setting.generated.h"

/**
 * 
 */
UCLASS()
class SS_FINAL_API URIM_Widget_Setting : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//[SetupPlayerInputComponent] 가상함수
	//void SetupPlayerInputComponent(class UEnhancedInputComponent* PlayerInputComponent);

public:
	//BeginPlay 와 같은 동작
	virtual void NativeConstruct() override;

	//[블루프린트 위젯을 C++과 연결]
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_close;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_save;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_main;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_exit;

public:
	UPROPERTY()
	class ACharacterBase* player;

public:
	//[버튼 연결 함수]
	UFUNCTION()
	void Bind_btn_close();
	UFUNCTION()
	void Bind_btn_save();
	UFUNCTION()
	void Bind_btn_main();
	UFUNCTION()
	void Bind_btn_exit();


};
