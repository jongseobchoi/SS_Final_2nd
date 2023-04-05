// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <UMG/Public/Components/Image.h>
#include "Widget_AssetMain.generated.h"

UCLASS()
class SS_FINAL_API UWidget_AssetMain : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//[SetupPlayerInputComponent] 가상함수
	//void SetupPlayerInputComponent(class UEnhancedInputComponent* PlayerInputComponent);

public:
	//BeginPlay 와 같은 동작
	virtual void NativeConstruct() override;

	//[블루프린트 위젯을 C++과 연결]
	//메인 카테고리 버튼
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_Category01; //가구
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_Category02; //조명
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_Category03; //가전제품
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_Category04; //기타

	//서브 카테고리 버튼
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_SubCategory1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_SubCategory2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_SubCategory3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_SubCategory4;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_SubCategory5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_SubCategory6;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_SubCategory7;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_SubCategory8;

	//제품 버튼
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_Product01;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_Product02;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_Product03;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_Product04;

	//닫기 버튼
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_Close;

	//장바구니 추가 버튼
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_AddCart01;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_AddCart02;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_AddCart03;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_AddCart04;

	//자세히보기 버튼(링크)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_detail01;


public:
	UPROPERTY()
	class AWidgetActor_AssetMain* widgetActor_AssetMain;

	UPROPERTY()
	class AJS_ProductManager* productManager;

	UPROPERTY()
	class ACharacterBase* player;


public:
	//[버튼 연결 함수]
	//메인 카테고리 버튼 연결
	UFUNCTION()
	void Bind_btn_Category01();
	UFUNCTION()
	void Bind_btn_Category02();
	UFUNCTION()
	void Bind_btn_Category03();
	UFUNCTION()
	void Bind_btn_Category04();

	//서브 카테고리 버튼 연결
	UFUNCTION()
	void Bind_btn_SubCategory1();
	UFUNCTION()
	void Bind_btn_SubCategory2();
	UFUNCTION()
	void Bind_btn_SubCategory3();
	UFUNCTION()
	void Bind_btn_SubCategory4();
	UFUNCTION()
	void Bind_btn_SubCategory5();
	UFUNCTION()
	void Bind_btn_SubCategory6();
	UFUNCTION()
	void Bind_btn_SubCategory7();
	UFUNCTION()
	void Bind_btn_SubCategory8();

	//제품 버튼 연결
	UFUNCTION()
	void Bind_btn_Product01();
	UFUNCTION()
	void Bind_btn_Product02();
	UFUNCTION()
	void Bind_btn_Product03();
	UFUNCTION()
	void Bind_btn_Product04();

	//닫기 버튼 연결
	UFUNCTION()
	void Bind_btn_Close();

	//장바구니 담기 버튼 연결
	UFUNCTION()
	void Bind_btn_AddCart01();
	UFUNCTION()
	void Bind_btn_AddCart02();
	UFUNCTION()
	void Bind_btn_AddCart03();
	UFUNCTION()
	void Bind_btn_AddCart04();

	//자세히보기 버튼(링크) 연결
	UFUNCTION()
	void Bind_btn_detail01();


public:
	UPROPERTY()
	class UCSVLoader* csvLoader;


public:
	//[서브 카테고리]
	UPROPERTY()
	TArray<class UTextBlock*> arrSubCategory; //서브 카테고리의 블루프린트 위젯에서 텍스트 배열

	void SetSubCategory(int32 category); //서브 카테고리 노출하는 함수. category = 매개변수. 가구/조명/가전제품/기타 중에 무엇을 클릭할 것인지 모르니까 허구로 넣음


public:
	//[제품 정보]
	UPROPERTY(EditAnywhere)
	TArray<class UTextBlock*> arrProductName; //제품 정보의 블루프린트 위젯에서 텍스트 배열
	UPROPERTY(EditAnywhere)
	TArray<class UTextBlock*> arrProductPrice;
	UPROPERTY(EditAnywhere)
	TArray<class UImage*> arrProductThumbnail;

	void SetProductInfo(int32 subCategory); //제품 노출하는 함수. subcategory = 매개변수. 소파/식탁/스탠드/TV ... 중에 무엇을 클릭할 것인지 모르니까 허구로 넣음

	int32 subCategoryStartIdx = 0; //★★★★★
	int32 productIdx = 0; //★★★★★

public:
	UPROPERTY()
	class ARIM_CartManager* cartManager;


public:
	////////////////////////////////////////////////////// 종섭이가

	// 활성/비활성 함수
	void SetActive(bool value);
	int32 selectedProductIdx = 0;
	
	void SelectProduct(int32 value);
};





