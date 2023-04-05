// Fill out your copyright notice in the Description page of Project Settings.


#include "RIM_Widget_ScreenShot.h"
#include <Kismet/GameplayStatics.h>
#include "CharacterBase.h"
#include "Components/Button.h"
#include <UMG/Public/Components/WidgetInteractionComponent.h>

//BeginPlay �� ���� ����
void URIM_Widget_ScreenShot::NativeConstruct()
{
	player = Cast<ACharacterBase>(UGameplayStatics::GetActorOfClass(GetWorld(), ACharacterBase::StaticClass())); //ĳ���͸� ã�ƿͼ� ĳ��Ʈ �� �־��ش�
	currentWorld = GetWorld();

	//[��ư Ŭ��]
	//��ũ���� ��ư ����
	btn_ScreenShot->OnPressed.AddDynamic(this, &URIM_Widget_ScreenShot::StartScreenShot);
	btn_close->OnPressed.AddDynamic(this, &URIM_Widget_ScreenShot::Close);
}

//ȭ��ĸó ����
void URIM_Widget_ScreenShot::StartScreenShot()
{
	//��ũ���� ������ �� ���δ�. �ݸ����� ���ݸ������� �Ѵ�
	player->SetWidgetActive(2, false); //------> �������� �۾��� �ڵ� ���
	 
	//��Ʈ�ѷ�, ������ �� ����(�������)
	player->meshLeftHand->SetVisibility(false);
	player->meshRightHand->SetVisibility(false);
	player->compWidgetPointer_right->bShowDebug = false;

	//1�� ���̵�
	Fade(); 

	//0.5�� �� ȭ�� ĸó
	ClickScreenShot();

	if (ClickScreenShotBtn != false)
	{
		//1�� �� ��ũ���� ����, ��Ʈ�ѷ� ����
		FTimerHandle WaitHandle;
		float WaitTime = 1.2f;
		currentWorld->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
			{
				//��ũ���� ������ ���δ�. �ݸ�����	UI �� �Ѵ�
				player->SetWidgetActive(2, true); //------> �������� �۾��� �ڵ� ���

				//��Ʈ�ѷ�, ������ ����
				player->meshLeftHand->SetVisibility(true);
				player->meshRightHand->SetVisibility(true);
				player->compWidgetPointer_right->bShowDebug = true;
			}), WaitTime, false);
	}
}

//���̵�
void URIM_Widget_ScreenShot::Fade()
{
	GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraFade(0, 0.5f, 0.5f, FLinearColor::Black);
}

//ȭ��ĸó ��(������, ���̵� ��)
void URIM_Widget_ScreenShot::ClickScreenShot()
{
	//[0.5�� �� ȭ���� ĸó�Ѵ�]
	FTimerHandle WaitHandle;
	float WaitTime = 0.5f;
	currentWorld->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
		{
			player->TakeScreenShot(); //ĸó ------> �������� �۾��� �ڵ� ���
		}), WaitTime, false);

	//�����Ǹ� ��Ĭ ȿ�� �߰��Ѵ�

	ClickScreenShotBtn = true;
}

void URIM_Widget_ScreenShot::Close()
{
	//��ũ���� ������ �� ���δ�. �ݸ����� ���ݸ������� �Ѵ�
	player->SetWidgetActive(2, false); //------> �������� �۾��� �ڵ� ���

	//�޼� �޴� ������ ���δ�. �ݸ����� UI �� �Ѵ�
	player->SetWidgetActive(0, true); //------> �������� �۾��� �ڵ� ���
}