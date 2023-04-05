// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CSVLoader.h"
#include "RIM_Widget_Order.generated.h"

/**
 * 
 */
UCLASS()
class SS_FINAL_API URIM_Widget_Order : public UUserWidget
{
	GENERATED_BODY()

public:
	//[SetupPlayerInputComponent] �����Լ�
	void SetupPlayerInputComponent(class UEnhancedInputComponent* PlayerInputComponent); //�̰� ��� �� �� ������...?

public:
	//BeginPlay �� ���� ����
	virtual void NativeConstruct() override;


public:
	UPROPERTY()
	class ARIM_WidgetActor_Order* widgetActor_Order; //���� ���� ����
	
	UPROPERTY()
	class UCSVLoader* csvLoader;

	UPROPERTY()
	class ACharacterBase* player;
	
	UPROPERTY()
	int32 total = 0;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* totalPrice; //�� �ݾ�

	UFUNCTION()
	void SetTotalPriceWidgetInCart();



};
