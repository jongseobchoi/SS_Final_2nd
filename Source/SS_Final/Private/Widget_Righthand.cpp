// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_Righthand.h"
#include <Kismet/GameplayStatics.h>
#include "Components/Button.h"
#include "WidgetActor_Righthand.h"
#include "CharacterBase.h"
#include <UMG/Public/Components/WidgetComponent.h>
#include "JS_CameraTopView.h"
#include <UMG/Public/Components/CheckBox.h>

//BeginPlay �� ���� ����
void UWidget_Righthand::NativeConstruct()
{
	player = Cast<ACharacterBase>(UGameplayStatics::GetActorOfClass(GetWorld(), ACharacterBase::StaticClass())); //ĳ���͸� �����ͼ� ĳ��Ʈ�ؼ� �־��ش�
	currentWorld = GetWorld();
	topViewCam = Cast<AJS_CameraTopView>(UGameplayStatics::GetActorOfClass(GetWorld(), AJS_CameraTopView::StaticClass()));

	//[��ư Ŭ��]
	btn_righthand01->OnPressed.AddDynamic(this, &UWidget_Righthand::Bind_btn_righthand01);
	btn_righthand02->OnPressed.AddDynamic(this, &UWidget_Righthand::Bind_btn_righthand02);
	btn_righthand03->OnPressed.AddDynamic(this, &UWidget_Righthand::Bind_btn_righthand03);
	btn_righthand04->OnPressed.AddDynamic(this, &UWidget_Righthand::Bind_btn_righthand04);

	checkBox_topview->OnCheckStateChanged.AddDynamic(this, &UWidget_Righthand::CheckBox_TopView_Checked);
	checkBox_night->OnCheckStateChanged.AddDynamic(this, &UWidget_Righthand::CheckBox_Night_Checked);

	AssetMainWidgetVisiable();
	ScreenShotWidgetVisiable();
	SettingWidgetVisiable();

}

//[��ư Ŭ���ϸ� (���Ϳ���) �Լ� ����]
//��ǰ ã�� ���� ����
void UWidget_Righthand::Bind_btn_righthand01()
{	
	//�޼� �޴� ������ �� ���δ�. �ݸ����� ���ݸ������� �Ѵ�
	player->SetWidgetActive(0,false); //------> �������� �۾��� �ڵ� ���

	//���� ���� ������ ������/���δ�
	player->SetWidgetActive(1, true); //------> �������� �۾��� �ڵ� ���

}

//��ũ���� �Կ� ���� ����
void UWidget_Righthand::Bind_btn_righthand02()
{
	//�޼� �޴� ������ �� ���δ�. �ݸ����� ���ݸ������� �Ѵ�
	player->SetWidgetActive(0, false); //------> �������� �۾��� �ڵ� ���

	FTimerHandle WaitHandle;
	float WaitTime = 0.5f;
	currentWorld->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
		{
			//0.5�� �� ��ũ���� ������ ����ȴ�
			player->SetWidgetActive(2, true); //��ũ���� ������ ���δ�. �ݸ����� UI �� �Ѵ� //------> �������� �۾��� �ڵ� ���
		}), WaitTime, false);
}

//��ٱ��� �̵� ����
void UWidget_Righthand::Bind_btn_righthand03()
{
	//�޼� �޴� ������ �� ���δ�. �ݸ����� ���ݸ������� �Ѵ�
	//player->SetWidgetActive(0, false);
	
	//��ٱ��� ������ ����. �̵��Ѵ�
	UGameplayStatics::OpenLevel(GetWorld(), "03_Cart");

}

//���� ���� ����
void UWidget_Righthand::Bind_btn_righthand04()
{
	//�޼� �޴� ������ �� ���δ�. �ݸ����� ���ݸ������� �Ѵ�
	player->SetWidgetActive(0, false); //------> �������� �۾��� �ڵ� ���
	
	//���� ������ ���δ�. �ݸ����� UI �� �Ѵ�
	player->SetWidgetActive(3, true); //------> �������� �۾��� �ڵ� ���
}

//ž�� ��ȯ
void UWidget_Righthand::CheckBox_TopView_Checked(bool isTopViewChecked)
{
	if (isTopViewChecked)
	{
		UE_LOG(LogTemp, Warning, TEXT("Checkbox -----> Topview -----> checked!!!!!"));
		//[ž�� �ѱ�] ------> �������� �۾��� �ڵ� ���
		//ī�޶� ž���
		player->playerCon->SetViewTarget(topViewCam);
		//ī�޶� ����
		player->ChangeState(EPlayerState::CameraMode);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Checkbox -----> Topview -----> unchecked!!!!!"));
		//[ž�� ����] ------> �������� �۾��� �ڵ� ���
		//ī�޶� ������ ������
		player->playerCon->SetViewTarget(player);
		//Idle ���·�
		player->ChangeState(EPlayerState::Idle);
	}
}

//�߰� ��� �Ѱ� ����
void UWidget_Righthand::CheckBox_Night_Checked(bool isNightChecked)
{
	if (isNightChecked)
	{
		UE_LOG(LogTemp, Warning, TEXT("Checkbox -----> Night -----> checked!!!!!"));
		//�߰� ��� �ѱ� ------> �������� �۾��� �ڵ� ���
		player->ChangeDayNight(isNight);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Checkbox -----> Night -----> unchecked!!!!!"));
		//�߰� ��� ���� ------> �������� �۾��� �ڵ� ���
		player->ChangeDayNight(!isNight);
	}
}

void UWidget_Righthand::AssetMainWidgetVisiable()
{
	if (AssetMainWidgetOpen != true) //�̳���
	{
		player->SetWidgetActive(1,false);
		AssetMainWidgetOpen = false;
	}
	else //����
	{
		player->SetWidgetActive(1, true);
		AssetMainWidgetOpen = true;
	}
}

void UWidget_Righthand::ScreenShotWidgetVisiable()
{
	if (ScreenShotWidgetOpen != true) //��ũ���� ������ �̳��� �̸�
	{
		player->SetWidgetActive(2, false); //��ũ���� ���� �� ���δ�
		ScreenShotWidgetOpen = false;
	}
	else //��ũ���� ������ ���� �̸�
	{
		player->SetWidgetActive(2, true); //��ũ���� ������ ���δ�
		ScreenShotWidgetOpen = true; 
	}
}

void UWidget_Righthand::SettingWidgetVisiable()
{
	if (SettingWidgetOpen != true)
	{
		player->SetWidgetActive(3, false);
		SettingWidgetOpen = false;
	}
	else
	{
		player->SetWidgetActive(3, true);
		SettingWidgetOpen = true;
	}
}