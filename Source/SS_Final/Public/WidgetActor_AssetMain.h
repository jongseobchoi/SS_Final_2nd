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
	//���� �߰�
	UPROPERTY(EditAnywhere)
	class UWidgetComponent* widget_AssetMain;

public:
	//[�������� ��ư Ŭ�� ���� �� ���� �� �Լ�]
	//��з� ��ư
	void Category01();
	void Category02();
	void Category03();
	void Category04();

	//�Һз� ��ư
	void type01();
	void type02();
	void type03();
	void type04();
	void type05();
	void type06();
	void type07();
	void type08();

	//��ǰ ��ư
	void product01();
	void product02();
	void product03();
	void product04();

};
