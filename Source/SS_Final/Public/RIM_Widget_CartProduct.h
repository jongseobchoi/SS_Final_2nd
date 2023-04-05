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
	//[SetupPlayerInputComponent] 가상함수
	void SetupPlayerInputComponent(class UEnhancedInputComponent* PlayerInputComponent); //없어도 될거 같은데...

public:
	//BeginPlay 와 같은 동작
	virtual void NativeConstruct() override;


public:
	//[배열]
	UPROPERTY(EditAnywhere)
	TArray<class UTextBlock*> arrProductName; //제품 정보의 블루프린트 위젯에서 텍스트 배열
	UPROPERTY(EditAnywhere)
	TArray<class UTextBlock*> arrProductPrice;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* productName; //제품 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* productPrice; //제품 가격
	
	//제품 삭제 버튼
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_Delete;

public:
	UPROPERTY()
	class UCSVLoader* csvLoader;

public:
	UPROPERTY()
	class ARIM_WidgetActor_CartProduct* widgetActor_CartProduct; //위젯 액터

	UFUNCTION()
	void SetProductInfoWidgetInCart(FWidgetProductInfo info);

	//제품 삭제 버튼
	UFUNCTION()
	void Bind_btn_Delete();







};
