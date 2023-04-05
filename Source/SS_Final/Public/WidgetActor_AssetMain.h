// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WidgetActor_AssetMain.generated.h"

UCLASS()
class SS_FINAL_API AWidgetActor_AssetMain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWidgetActor_AssetMain();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	//위젯 추가
	UPROPERTY(EditAnywhere)
	class UWidgetComponent* widget_AssetMain;

public:
	//[위젯에서 버튼 클릭 했을 때 실행 될 함수]
	//대분류 버튼
	void Category01();
	void Category02();
	void Category03();
	void Category04();

	//소분류 버튼
	void type01();
	void type02();
	void type03();
	void type04();
	void type05();
	void type06();
	void type07();
	void type08();

	//제품 버튼
	void product01();
	void product02();
	void product03();
	void product04();

};
