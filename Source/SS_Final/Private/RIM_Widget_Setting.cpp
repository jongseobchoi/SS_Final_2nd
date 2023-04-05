// Fill out your copyright notice in the Description page of Project Settings.


#include "RIM_Widget_Setting.h"
#include <Kismet/GameplayStatics.h>
#include "Components/Button.h"
#include "CharacterBase.h"
#include <UMG/Public/Components/WidgetComponent.h>
#include "Components/CheckBox.h"
#include <Engine/DirectionalLight.h>

//BeginPlay 와 같은 동작
void URIM_Widget_Setting::NativeConstruct()
{
	player = Cast<ACharacterBase>(UGameplayStatics::GetActorOfClass(GetWorld(), ACharacterBase::StaticClass()));

	//[버튼 클릭]
	btn_close->OnPressed.AddDynamic(this, &URIM_Widget_Setting::Bind_btn_close);
	btn_save->OnPressed.AddDynamic(this, &URIM_Widget_Setting::Bind_btn_save);
	btn_main->OnPressed.AddDynamic(this, &URIM_Widget_Setting::Bind_btn_main);
	btn_exit->OnPressed.AddDynamic(this, &URIM_Widget_Setting::Bind_btn_exit);
	

}

//[버튼 클릭하면 (액터에서) 함수 실행]
//위젯 닫기
void URIM_Widget_Setting::Bind_btn_close()
{
	//세팅 위젯이 안 보인다. 콜리전을 노콜리전으로 한다
	player->SetWidgetActive(3, false);

	//왼손 메뉴 위젯이 보인다. 콜리전을 UI 로 한다
	player->SetWidgetActive(0, true);
}

//현재 프로젝트 저장
void URIM_Widget_Setting::Bind_btn_save()
{
	//현재 프로젝트 저장
	//★★★★★ 코드 추가 필요 ★★★★★
}

//메인 레벨로 이동
void URIM_Widget_Setting::Bind_btn_main()
{
	//프로젝트 선택 레벨로 이동
	//★★★★★ 코드 추가 필요 ★★★★★
}

//플레이 종료
void URIM_Widget_Setting::Bind_btn_exit()
{
	//플레이 종료
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}