// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RIM_WidgetActor_CartProduct.generated.h"

UCLASS()
class SS_FINAL_API ARIM_WidgetActor_CartProduct : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARIM_WidgetActor_CartProduct();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
public:
	//À§Á¬ Ãß°¡
	UPROPERTY(EditAnywhere)
	class UWidgetComponent* widget_CartProduct;


};
