// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProductBase.h"
#include "ElectronicBase.generated.h"

/**
 * 
 */
UCLASS()
class SS_FINAL_API AElectronicBase : public AProductBase
{
	GENERATED_BODY()

public:
	AElectronicBase();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
