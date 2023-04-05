// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JS_CameraBase.h"
#include "JS_CameraTopView.generated.h"

/**
 * 
 */
UCLASS()
class SS_FINAL_API AJS_CameraTopView : public AJS_CameraBase
{
	GENERATED_BODY()
	

public:
	// Sets default values for this character's properties
	AJS_CameraTopView();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

// 	// Called to bind functionality to input
// 	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// ��Ʈ ������Ʈ�� �� ������Ʈ
	UPROPERTY(EditAnywhere)
	class USceneComponent* compScene;
	// ������ �� ������Ʈ
	UPROPERTY(EditAnywhere)
	class USpringArmComponent* compArm;
	// ī�޶� ������Ʈ
	UPROPERTY(EditAnywhere)
	class UCameraComponent* compCam;
};
