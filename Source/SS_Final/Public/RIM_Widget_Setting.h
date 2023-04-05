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
	//[SetupPlayerInputComponent] �����Լ�
	//void SetupPlayerInputComponent(class UEnhancedInputComponent* PlayerInputComponent);

public:
	//BeginPlay �� ���� ����
	virtual void NativeConstruct() override;

	//[�������Ʈ ������ C++�� ����]
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
	//[��ư ���� �Լ�]
	UFUNCTION()
	void Bind_btn_close();
	UFUNCTION()
	void Bind_btn_save();
	UFUNCTION()
	void Bind_btn_main();
	UFUNCTION()
	void Bind_btn_exit();


};
