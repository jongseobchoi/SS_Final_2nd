// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RIM_WidgetActor_Order.generated.h"

UCLASS()
class SS_FINAL_API ARIM_WidgetActor_Order : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARIM_WidgetActor_Order();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	//오더 위젯 추가
	UPROPERTY(EditAnywhere)
	class UWidgetComponent* widget_Order;

};
