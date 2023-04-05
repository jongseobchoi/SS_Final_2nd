// Fill out your copyright notice in the Description page of Project Settings.


#include "RIM_Widget_Title.h"
#include <Kismet/GameplayStatics.h>
#include "Components/Button.h"
#include "RIM_WidgetActor_Title.h"

//BeginPlay �� ���� ����
void URIM_Widget_Title::NativeConstruct()
{
	//[��ư Ŭ��]
	btn_PlayStart->OnPressed.AddDynamic(this, &URIM_Widget_Title::Bind_btn_PlayStart);


}

//[��ư Ŭ���ϸ� ���Ϳ��� �Լ� ����]
void URIM_Widget_Title::Bind_btn_PlayStart()
{
	widgetActor_Title->PlayStart();

}
