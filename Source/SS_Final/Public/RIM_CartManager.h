// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSVLoader.h"
#include "RIM_CartManager.generated.h"

UCLASS()
class SS_FINAL_API ARIM_CartManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARIM_CartManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	UPROPERTY()
	class UCSVLoader* csvLoader;

	UPROPERTY()
	class ARIM_CartProduct* cartProduct;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ARIM_CartProduct> cartProductFactory; //스태틱메시(제품) 생성 등록

	UPROPERTY()
	class URIM_Widget_CartProduct* widgetCartProduct;

public:
	UFUNCTION()
	void SetProductInfoInCart();

// 	UPROPERTY()
// 	int32 total = 0;

	UPROPERTY()
	float currentTime = 0;

	//장바구니에 담은 수량
	UPROPERTY()
	int32 x = 0;

	//장바구니 담기 버튼 클릭한 제품 정보
	UPROPERTY()
	TArray<FWidgetProductInfo> id;



	//삭제 테스트
// 	UFUNCTION()
// 	void DeleteProductInCart(FWidgetProductInfo id);

};
