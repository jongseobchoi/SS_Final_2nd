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
	TSubclassOf<class ARIM_CartProduct> cartProductFactory; //����ƽ�޽�(��ǰ) ���� ���

	UPROPERTY()
	class URIM_Widget_CartProduct* widgetCartProduct;

public:
	UFUNCTION()
	void SetProductInfoInCart();

// 	UPROPERTY()
// 	int32 total = 0;

	UPROPERTY()
	float currentTime = 0;

	//��ٱ��Ͽ� ���� ����
	UPROPERTY()
	int32 x = 0;

	//��ٱ��� ��� ��ư Ŭ���� ��ǰ ����
	UPROPERTY()
	TArray<FWidgetProductInfo> id;



	//���� �׽�Ʈ
// 	UFUNCTION()
// 	void DeleteProductInCart(FWidgetProductInfo id);

};
