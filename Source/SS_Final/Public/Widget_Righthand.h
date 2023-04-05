// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_Righthand.generated.h"

/**
 * 
 */
UCLASS()
class SS_FINAL_API UWidget_Righthand : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//[SetupPlayerInputComponent] 가상함수
	//void SetupPlayerInputComponent(class UEnhancedInputComponent* PlayerInputComponent);

public:
	//BeginPlay 와 같은 동작
	virtual void NativeConstruct() override;

	//[블루프린트 위젯을 C++과 연결]
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_righthand01;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_righthand02;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_righthand03;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_righthand04;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UCheckBox* checkBox_topview;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UCheckBox* checkBox_night;

public:
	UPROPERTY()
	class AWidgetActor_Righthand* widgetActor_Righthand;

	UPROPERTY()
	class ACharacterBase* player;

	UPROPERTY()
	class UWorld* currentWorld;

	//월드에 있는 탑뷰 카메라 
	UPROPERTY()
	class AJS_CameraTopView* topViewCam; //------> 종섭님이 작업한 코드 사용

	//플레이어 컨트롤러
	UPROPERTY()
	APlayerController* playerCon; //------> 종섭님이 작업한 코드 사용

	//낮/밤 판별 변수
	UPROPERTY(EditAnywhere)
	bool isNight = false; //------> 종섭님이 작업한 코드 사용

public:
	//[버튼 연결 함수]
	UFUNCTION()
	void Bind_btn_righthand01();
	UFUNCTION()
	void Bind_btn_righthand02();
	UFUNCTION()
	void Bind_btn_righthand03();
	UFUNCTION()
	void Bind_btn_righthand04();

	UFUNCTION()
	void CheckBox_TopView_Checked(bool isTopViewChecked);
	UFUNCTION()
	void CheckBox_Night_Checked(bool isNightChecked);

	bool AssetMainWidgetOpen = false; //미노출
	bool ScreenShotWidgetOpen = false; //미노출
	bool SettingWidgetOpen = false; //미노출

	void  AssetMainWidgetVisiable();
	void  ScreenShotWidgetVisiable();
	void  SettingWidgetVisiable();



};
