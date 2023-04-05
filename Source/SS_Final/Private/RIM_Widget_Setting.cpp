// Fill out your copyright notice in the Description page of Project Settings.


#include "RIM_Widget_Setting.h"
#include <Kismet/GameplayStatics.h>
#include "Components/Button.h"
#include "CharacterBase.h"
#include <UMG/Public/Components/WidgetComponent.h>
#include "Components/CheckBox.h"
#include <Engine/DirectionalLight.h>

//BeginPlay �� ���� ����
void URIM_Widget_Setting::NativeConstruct()
{
	player = Cast<ACharacterBase>(UGameplayStatics::GetActorOfClass(GetWorld(), ACharacterBase::StaticClass()));

	//[��ư Ŭ��]
	btn_close->OnPressed.AddDynamic(this, &URIM_Widget_Setting::Bind_btn_close);
	btn_save->OnPressed.AddDynamic(this, &URIM_Widget_Setting::Bind_btn_save);
	btn_main->OnPressed.AddDynamic(this, &URIM_Widget_Setting::Bind_btn_main);
	btn_exit->OnPressed.AddDynamic(this, &URIM_Widget_Setting::Bind_btn_exit);
	

}

//[��ư Ŭ���ϸ� (���Ϳ���) �Լ� ����]
//���� �ݱ�
void URIM_Widget_Setting::Bind_btn_close()
{
	//���� ������ �� ���δ�. �ݸ����� ���ݸ������� �Ѵ�
	player->SetWidgetActive(3, false);

	//�޼� �޴� ������ ���δ�. �ݸ����� UI �� �Ѵ�
	player->SetWidgetActive(0, true);
}

//���� ������Ʈ ����
void URIM_Widget_Setting::Bind_btn_save()
{
	//���� ������Ʈ ����
	//�ڡڡڡڡ� �ڵ� �߰� �ʿ� �ڡڡڡڡ�
}

//���� ������ �̵�
void URIM_Widget_Setting::Bind_btn_main()
{
	//������Ʈ ���� ������ �̵�
	//�ڡڡڡڡ� �ڵ� �߰� �ʿ� �ڡڡڡڡ�
}

//�÷��� ����
void URIM_Widget_Setting::Bind_btn_exit()
{
	//�÷��� ����
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}