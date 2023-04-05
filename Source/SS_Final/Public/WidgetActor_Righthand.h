// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WidgetActor_Righthand.generated.h"

UCLASS()
class SS_FINAL_API AWidgetActor_Righthand : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWidgetActor_Righthand();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	//위젯 추가
	UPROPERTY(EditAnywhere)
	class UWidgetComponent* widget_Righthand;

	UPROPERTY()
	class ACharacterBase* player;

public:
	//[위젯에서 버튼 클릭 했을 때 실행 될 함수]
	void Righthand01();
	void Righthand02();
	void Righthand03();
	void Righthand04();
	void Righthand05();
	void Righthand06();
	void Righthand07();
	void Righthand08();


};
