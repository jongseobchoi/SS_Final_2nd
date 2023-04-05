// Fill out your copyright notice in the Description page of Project Settings.


#include "RIM_Widget_Title.h"
#include <Kismet/GameplayStatics.h>
#include "Components/Button.h"
#include "RIM_WidgetActor_Title.h"

//BeginPlay 와 같은 동작
void URIM_Widget_Title::NativeConstruct()
{
	//[버튼 클릭]
	btn_PlayStart->OnPressed.AddDynamic(this, &URIM_Widget_Title::Bind_btn_PlayStart);


}

//[버튼 클릭하면 액터에서 함수 실행]
void URIM_Widget_Title::Bind_btn_PlayStart()
{
	widgetActor_Title->PlayStart();

}
