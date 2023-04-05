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
	//[SetupPlayerInputComponent] �����Լ�
	//void SetupPlayerInputComponent(class UEnhancedInputComponent* PlayerInputComponent);

public:
	//BeginPlay �� ���� ����
	virtual void NativeConstruct() override;

	//[�������Ʈ ������ C++�� ����]
	//���� ī�װ� ��ư
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_Category01; //����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_Category02; //����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_Category03; //������ǰ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_Category04; //��Ÿ

	//���� ī�װ� ��ư
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

	//��ǰ ��ư
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_Product01;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_Product02;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_Product03;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_Product04;

	//�ݱ� ��ư
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_Close;

	//��ٱ��� �߰� ��ư
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_AddCart01;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_AddCart02;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_AddCart03;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_AddCart04;

	//�ڼ������� ��ư(��ũ)
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
	//[��ư ���� �Լ�]
	//���� ī�װ� ��ư ����
	UFUNCTION()
	void Bind_btn_Category01();
	UFUNCTION()
	void Bind_btn_Category02();
	UFUNCTION()
	void Bind_btn_Category03();
	UFUNCTION()
	void Bind_btn_Category04();

	//���� ī�װ� ��ư ����
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

	//��ǰ ��ư ����
	UFUNCTION()
	void Bind_btn_Product01();
	UFUNCTION()
	void Bind_btn_Product02();
	UFUNCTION()
	void Bind_btn_Product03();
	UFUNCTION()
	void Bind_btn_Product04();

	//�ݱ� ��ư ����
	UFUNCTION()
	void Bind_btn_Close();

	//��ٱ��� ��� ��ư ����
	UFUNCTION()
	void Bind_btn_AddCart01();
	UFUNCTION()
	void Bind_btn_AddCart02();
	UFUNCTION()
	void Bind_btn_AddCart03();
	UFUNCTION()
	void Bind_btn_AddCart04();

	//�ڼ������� ��ư(��ũ) ����
	UFUNCTION()
	void Bind_btn_detail01();


public:
	UPROPERTY()
	class UCSVLoader* csvLoader;


public:
	//[���� ī�װ�]
	UPROPERTY()
	TArray<class UTextBlock*> arrSubCategory; //���� ī�װ��� �������Ʈ �������� �ؽ�Ʈ �迭

	void SetSubCategory(int32 category); //���� ī�װ� �����ϴ� �Լ�. category = �Ű�����. ����/����/������ǰ/��Ÿ �߿� ������ Ŭ���� ������ �𸣴ϱ� �㱸�� ����


public:
	//[��ǰ ����]
	UPROPERTY(EditAnywhere)
	TArray<class UTextBlock*> arrProductName; //��ǰ ������ �������Ʈ �������� �ؽ�Ʈ �迭
	UPROPERTY(EditAnywhere)
	TArray<class UTextBlock*> arrProductPrice;
	UPROPERTY(EditAnywhere)
	TArray<class UImage*> arrProductThumbnail;

	void SetProductInfo(int32 subCategory); //��ǰ �����ϴ� �Լ�. subcategory = �Ű�����. ����/��Ź/���ĵ�/TV ... �߿� ������ Ŭ���� ������ �𸣴ϱ� �㱸�� ����

	int32 subCategoryStartIdx = 0; //�ڡڡڡڡ�
	int32 productIdx = 0; //�ڡڡڡڡ�

public:
	UPROPERTY()
	class ARIM_CartManager* cartManager;


public:
	////////////////////////////////////////////////////// �����̰�

	// Ȱ��/��Ȱ�� �Լ�
	void SetActive(bool value);
	int32 selectedProductIdx = 0;
	
	void SelectProduct(int32 value);
};





