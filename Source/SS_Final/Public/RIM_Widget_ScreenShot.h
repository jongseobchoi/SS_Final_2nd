// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RIM_Widget_ScreenShot.generated.h"

/**
 * 
 */
UCLASS()
class SS_FINAL_API URIM_Widget_ScreenShot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//[SetupPlayerInputComponent] �����Լ�
	//void SetupPlayerInputComponent(class UEnhancedInputComponent* PlayerInputComponent);

public:
	//BeginPlay �� ���� ����
	virtual void NativeConstruct() override;

public:
	//[�������Ʈ ������ C++�� ����]
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_ScreenShot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_close;

public:
	UPROPERTY()
	class ACharacterBase* player;

	UPROPERTY()
	class UWorld* currentWorld;

	UFUNCTION()
	void StartScreenShot();
	UFUNCTION()
	void Close();

	UFUNCTION()
	void Fade();

	UFUNCTION()
	void ClickScreenShot();
	bool ClickScreenShotBtn = false;

};
