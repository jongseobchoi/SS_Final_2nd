// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_Righthand.h"
#include <Kismet/GameplayStatics.h>
#include "Components/Button.h"
#include "WidgetActor_Righthand.h"
#include "CharacterBase.h"
#include <UMG/Public/Components/WidgetComponent.h>
#include "JS_CameraTopView.h"
#include <UMG/Public/Components/CheckBox.h>

//BeginPlay 와 같은 동작
void UWidget_Righthand::NativeConstruct()
{
	player = Cast<ACharacterBase>(UGameplayStatics::GetActorOfClass(GetWorld(), ACharacterBase::StaticClass())); //캐릭터를 가져와서 캐스트해서 넣어준다
	currentWorld = GetWorld();
	topViewCam = Cast<AJS_CameraTopView>(UGameplayStatics::GetActorOfClass(GetWorld(), AJS_CameraTopView::StaticClass()));

	//[버튼 클릭]
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

//[버튼 클릭하면 (액터에서) 함수 실행]
//제품 찾기 위젯 열기
void UWidget_Righthand::Bind_btn_righthand01()
{	
	//왼손 메뉴 위젯이 안 보인다. 콜리전을 노콜리전으로 한다
	player->SetWidgetActive(0,false); //------> 종섭님이 작업한 코드 사용

	//가구 메인 위젯이 열린다/보인다
	player->SetWidgetActive(1, true); //------> 종섭님이 작업한 코드 사용

}

//스크린샷 촬영 위젯 열기
void UWidget_Righthand::Bind_btn_righthand02()
{
	//왼손 메뉴 위젯이 안 보인다. 콜리전을 노콜리전으로 한다
	player->SetWidgetActive(0, false); //------> 종섭님이 작업한 코드 사용

	FTimerHandle WaitHandle;
	float WaitTime = 0.5f;
	currentWorld->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
		{
			//0.5초 후 스크린샷 위젯이 노출된다
			player->SetWidgetActive(2, true); //스크린샷 위젯이 보인다. 콜리전을 UI 로 한다 //------> 종섭님이 작업한 코드 사용
		}), WaitTime, false);
}

//장바구니 이동 열기
void UWidget_Righthand::Bind_btn_righthand03()
{
	//왼손 메뉴 위젯이 안 보인다. 콜리전을 노콜리전으로 한다
	//player->SetWidgetActive(0, false);
	
	//장바구니 레벨을 연다. 이동한다
	UGameplayStatics::OpenLevel(GetWorld(), "03_Cart");

}

//세팅 위젯 열기
void UWidget_Righthand::Bind_btn_righthand04()
{
	//왼손 메뉴 위젯이 안 보인다. 콜리전을 노콜리전으로 한다
	player->SetWidgetActive(0, false); //------> 종섭님이 작업한 코드 사용
	
	//세팅 위젯이 보인다. 콜리전을 UI 로 한다
	player->SetWidgetActive(3, true); //------> 종섭님이 작업한 코드 사용
}

//탑뷰 전환
void UWidget_Righthand::CheckBox_TopView_Checked(bool isTopViewChecked)
{
	if (isTopViewChecked)
	{
		UE_LOG(LogTemp, Warning, TEXT("Checkbox -----> Topview -----> checked!!!!!"));
		//[탑뷰 켜기] ------> 종섭님이 작업한 코드 사용
		//카메라를 탑뷰로
		player->playerCon->SetViewTarget(topViewCam);
		//카메라 모드로
		player->ChangeState(EPlayerState::CameraMode);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Checkbox -----> Topview -----> unchecked!!!!!"));
		//[탑뷰 끄기] ------> 종섭님이 작업한 코드 사용
		//카메라를 원래의 것으로
		player->playerCon->SetViewTarget(player);
		//Idle 상태로
		player->ChangeState(EPlayerState::Idle);
	}
}

//야간 모드 켜고 끄기
void UWidget_Righthand::CheckBox_Night_Checked(bool isNightChecked)
{
	if (isNightChecked)
	{
		UE_LOG(LogTemp, Warning, TEXT("Checkbox -----> Night -----> checked!!!!!"));
		//야간 모드 켜기 ------> 종섭님이 작업한 코드 사용
		player->ChangeDayNight(isNight);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Checkbox -----> Night -----> unchecked!!!!!"));
		//야간 모드 끄기 ------> 종섭님이 작업한 코드 사용
		player->ChangeDayNight(!isNight);
	}
}

void UWidget_Righthand::AssetMainWidgetVisiable()
{
	if (AssetMainWidgetOpen != true) //미노출
	{
		player->SetWidgetActive(1,false);
		AssetMainWidgetOpen = false;
	}
	else //노출
	{
		player->SetWidgetActive(1, true);
		AssetMainWidgetOpen = true;
	}
}

void UWidget_Righthand::ScreenShotWidgetVisiable()
{
	if (ScreenShotWidgetOpen != true) //스크린샷 위젯이 미노출 이면
	{
		player->SetWidgetActive(2, false); //스크린샷 위젯 안 보인다
		ScreenShotWidgetOpen = false;
	}
	else //스크린샷 위젯이 노출 이면
	{
		player->SetWidgetActive(2, true); //스크랜샷 위젯이 보인다
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