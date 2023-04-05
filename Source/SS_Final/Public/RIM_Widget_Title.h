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
	//[SetupPlayerInputComponent] �����Լ�
	void SetupPlayerInputComponent(class UEnhancedInputComponent* PlayerInputComponent); //�̰� ��� �� �� ������...?

public:
	//BeginPlay �� ���� ����
	virtual void NativeConstruct() override;

public:
	//[�������Ʈ ������ C++�� ����]
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_PlayStart; //���� ��ư


public:
	UPROPERTY()
	class ARIM_WidgetActor_Title* widgetActor_Title; //Ÿ��Ʋ ���� ����


public:
	//[��ư ���� �Լ�]
	UFUNCTION()
	void Bind_btn_PlayStart();



};
