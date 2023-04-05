// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TeleportLocationRingActor.generated.h"

UCLASS()
class SS_FINAL_API ATeleportLocationRingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATeleportLocationRingActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	//[텔레포트(이동) 위치 링]
	//나이아가라(이펙트)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UNiagaraComponent* compNiagara;


};
