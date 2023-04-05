// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CSVLoader.generated.h"

USTRUCT(BlueprintType) //��ǰ ���� ����ü
struct FWidgetProductInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FString name; //��ǰ �̸�
	UPROPERTY(EditAnywhere)
	int32 price; //��ǰ ����
	UPROPERTY(EditAnywhere)
	UTexture2D* thumbnail; //��ǰ �����
	UPROPERTY(EditAnywhere)
	UStaticMesh* mesh; //��ǰ
	UPROPERTY(EditAnywhere)
	int32 id;


};

UCLASS()
class SS_FINAL_API UCSVLoader : public UGameInstance // ---> Actor ���� GameInstance ��� ����. �ٸ� �������� ���� �����ϵ���

{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UCSVLoader();

protected:
	// Called when the game starts or when spawned
	virtual void Init() override;




public:
	//[���� ī�װ�]
	int32 columMax = 0; //����(��)

	UPROPERTY(EditAnywhere)	
	TArray<FString> arrCategory; //���δ�ƮŸ��.csv ���� �ʿ���, ������ �����͸� �����ϴ� �迭

	TArray<FString> GetCategoryItem(int32 category);

public:
	//[��ǰ]
	int32 productInfoColumMax = 0; //����(��)

	UPROPERTY(EditAnywhere)
	TArray<FWidgetProductInfo> arrProductInfo; //�ڡڡڿ� FWidgetProductInfo ���� ���? ���δ�Ʈ����.csv ���� �ʿ���, ������ �����͸� �����ϴ� �迭

	TArray<FWidgetProductInfo> GetProductInfo(int32 subCategory);

	UPROPERTY(EditAnywhere)
	TMap<int32, FWidgetProductInfo> mapProdutInfo; //��ǰ �ڵ�(id) �����ϴ� �迭

	UPROPERTY(EditAnywhere)

	TArray<int32> arrCart; //�ڡڡڡڡ�??? ��ǰ ���̵�(����) �迭?
	void AddCart(int32 productIndex); //�ڡڡڡڡ�productIndex �� �������� ����� �ȳ�... �� ��

public:
	//void GetProductInfoInCart();

	TArray<FWidgetProductInfo> GetProductInfoInCart();



};
