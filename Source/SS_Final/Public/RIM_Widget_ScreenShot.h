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
	//[SetupPlayerInputComponent] 가상함수
	//void SetupPlayerInputComponent(class UEnhancedInputComponent* PlayerInputComponent);

public:
	//BeginPlay 와 같은 동작
	virtual void NativeConstruct() override;

public:
	//[블루프린트 위젯을 C++과 연결]
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
