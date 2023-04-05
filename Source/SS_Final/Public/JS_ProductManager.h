// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSVLoader.h"
#include "JS_ProductManager.generated.h"

UCLASS()
class SS_FINAL_API AJS_ProductManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJS_ProductManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	class AProductBase* product;
	UPROPERTY(EditAnywhere)
	class UCSVLoader* CSVLoader;
	UPROPERTY(EditAnywhere)
	TArray<AProductBase*> productArr;

	UPROPERTY(EditAnywhere)
	class AJS_ProductGhost* ghostClass;

	UPROPERTY(EditAnywhere)
	class ACharacterBase* player;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AProductBase> currProduct;
	int32 selectedWidgetIdx;

	// 제품 위젯 변수
	UPROPERTY(EditAnywhere)
	class AJS_WidgetActor* smallWidget;
	// 제품 위젯 담을 변수
	UPROPERTY(EditAnywhere)
	TSubclassOf<AJS_WidgetActor> smallWidgetFactory;
	// 스폰한 위젯 변수
	UPROPERTY(EditAnywhere)
	class AJS_WidgetActor* spawnedSmallWidget;

	class AProductBase* selectedProduct;
	class ALightBase* selectedLightProduct;
	class ALightBase* lightProduct;
	void SelectedProduct(int32 value);
};
