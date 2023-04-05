// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProductBase.h"
#include "LightBase.generated.h"

/**
 * 
 */
UCLASS()
class SS_FINAL_API ALightBase : public AProductBase
{
	GENERATED_BODY()
	
public:
	ALightBase();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	
public:
	bool bLight = false;
	UPROPERTY(VisibleAnywhere)
	class USpotLightComponent* compLight;
	UPROPERTY(VisibleAnywhere)
	TArray<USpotLightComponent*> lightComponents;

	void SetLights();
	void SwitchLights();
};
