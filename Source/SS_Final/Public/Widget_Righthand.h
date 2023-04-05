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
	//[SetupPlayerInputComponent] �����Լ�
	//void SetupPlayerInputComponent(class UEnhancedInputComponent* PlayerInputComponent);

public:
	//BeginPlay �� ���� ����
	virtual void NativeConstruct() override;

	//[�������Ʈ ������ C++�� ����]
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

	//���忡 �ִ� ž�� ī�޶� 
	UPROPERTY()
	class AJS_CameraTopView* topViewCam; //------> �������� �۾��� �ڵ� ���

	//�÷��̾� ��Ʈ�ѷ�
	UPROPERTY()
	APlayerController* playerCon; //------> �������� �۾��� �ڵ� ���

	//��/�� �Ǻ� ����
	UPROPERTY(EditAnywhere)
	bool isNight = false; //------> �������� �۾��� �ڵ� ���

public:
	//[��ư ���� �Լ�]
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

	bool AssetMainWidgetOpen = false; //�̳���
	bool ScreenShotWidgetOpen = false; //�̳���
	bool SettingWidgetOpen = false; //�̳���

	void  AssetMainWidgetVisiable();
	void  ScreenShotWidgetVisiable();
	void  SettingWidgetVisiable();



};
