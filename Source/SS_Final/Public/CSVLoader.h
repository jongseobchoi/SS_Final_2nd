// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CSVLoader.generated.h"

USTRUCT(BlueprintType) //제품 정보 구조체
struct FWidgetProductInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FString name; //제품 이름
	UPROPERTY(EditAnywhere)
	int32 price; //제품 가격
	UPROPERTY(EditAnywhere)
	UTexture2D* thumbnail; //제품 썸네일
	UPROPERTY(EditAnywhere)
	UStaticMesh* mesh; //제품
	UPROPERTY(EditAnywhere)
	int32 id;


};

UCLASS()
class SS_FINAL_API UCSVLoader : public UGameInstance // ---> Actor 에서 GameInstance 상속 변경. 다른 레벨에서 적용 가능하도록

{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UCSVLoader();

protected:
	// Called when the game starts or when spawned
	virtual void Init() override;




public:
	//[서브 카테고리]
	int32 columMax = 0; //세로(열)

	UPROPERTY(EditAnywhere)	
	TArray<FString> arrCategory; //프로덕트타입.csv 에서 필요한, 선별한 데이터를 저장하는 배열

	TArray<FString> GetCategoryItem(int32 category);

public:
	//[제품]
	int32 productInfoColumMax = 0; //세로(열)

	UPROPERTY(EditAnywhere)
	TArray<FWidgetProductInfo> arrProductInfo; //★★★왜 FWidgetProductInfo 으로 사용? 프로덕트정보.csv 에서 필요한, 선별한 데이터를 저장하는 배열

	TArray<FWidgetProductInfo> GetProductInfo(int32 subCategory);

	UPROPERTY(EditAnywhere)
	TMap<int32, FWidgetProductInfo> mapProdutInfo; //상품 코드(id) 저장하는 배열

	UPROPERTY(EditAnywhere)

	TArray<int32> arrCart; //★★★★★??? 제품 아이디(숫자) 배열?
	void AddCart(int32 productIndex); //★★★★★productIndex 가 뭐였는지 기억이 안남... ㅠ ㅠ

public:
	//void GetProductInfoInCart();

	TArray<FWidgetProductInfo> GetProductInfoInCart();



};
