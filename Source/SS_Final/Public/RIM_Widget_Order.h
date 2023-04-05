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
	//[SetupPlayerInputComponent] 가상함수
	void SetupPlayerInputComponent(class UEnhancedInputComponent* PlayerInputComponent); //이거 없어도 될 거 같은데...?

public:
	//BeginPlay 와 같은 동작
	virtual void NativeConstruct() override;


public:
	UPROPERTY()
	class ARIM_WidgetActor_Order* widgetActor_Order; //오더 위젯 액터
	
	UPROPERTY()
	class UCSVLoader* csvLoader;

	UPROPERTY()
	class ACharacterBase* player;
	
	UPROPERTY()
	int32 total = 0;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* totalPrice; //총 금액

	UFUNCTION()
	void SetTotalPriceWidgetInCart();



};
