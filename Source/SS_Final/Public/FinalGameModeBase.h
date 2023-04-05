// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FinalGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SS_FINAL_API AFinalGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFinalGameModeBase(); //�߰�

protected:
	virtual void BeginPlay() override; //�߰�

public:
	virtual void Tick(float DeltaTime) override; //�߰�
	

};
