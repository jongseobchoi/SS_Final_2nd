// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CSVLoader.h"
#include "RIM_Widget_CartProduct.generated.h"

/**
 * 
 */
UCLASS()
class SS_FINAL_API URIM_Widget_CartProduct : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//[SetupPlayerInputComponent] �����Լ�
	void SetupPlayerInputComponent(class UEnhancedInputComponent* PlayerInputComponent); //��� �ɰ� ������...

public:
	//BeginPlay �� ���� ����
	virtual void NativeConstruct() override;


public:
	//[�迭]
	UPROPERTY(EditAnywhere)
	TArray<class UTextBlock*> arrProductName; //��ǰ ������ �������Ʈ �������� �ؽ�Ʈ �迭
	UPROPERTY(EditAnywhere)
	TArray<class UTextBlock*> arrProductPrice;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* productName; //��ǰ �̸�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* productPrice; //��ǰ ����
	
	//��ǰ ���� ��ư
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_Delete;

public:
	UPROPERTY()
	class UCSVLoader* csvLoader;

public:
	UPROPERTY()
	class ARIM_WidgetActor_CartProduct* widgetActor_CartProduct; //���� ����

	UFUNCTION()
	void SetProductInfoWidgetInCart(FWidgetProductInfo info);

	//��ǰ ���� ��ư
	UFUNCTION()
	void Bind_btn_Delete();







};
