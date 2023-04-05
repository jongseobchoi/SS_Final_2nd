// Fill out your copyright notice in the Description page of Project Settings.


#include "RIM_Widget_ScreenShot.h"
#include <Kismet/GameplayStatics.h>
#include "CharacterBase.h"
#include "Components/Button.h"
#include <UMG/Public/Components/WidgetInteractionComponent.h>

//BeginPlay 와 같은 동작
void URIM_Widget_ScreenShot::NativeConstruct()
{
	player = Cast<ACharacterBase>(UGameplayStatics::GetActorOfClass(GetWorld(), ACharacterBase::StaticClass())); //캐릭터를 찾아와서 캐스트 후 넣어준다
	currentWorld = GetWorld();

	//[버튼 클릭]
	//스크린샷 버튼 연결
	btn_ScreenShot->OnPressed.AddDynamic(this, &URIM_Widget_ScreenShot::StartScreenShot);
	btn_close->OnPressed.AddDynamic(this, &URIM_Widget_ScreenShot::Close);
}

//화면캡처 실행
void URIM_Widget_ScreenShot::StartScreenShot()
{
	//스크린샷 위젯이 안 보인다. 콜리전을 노콜리전으로 한다
	player->SetWidgetActive(2, false); //------> 종섭님이 작업한 코드 사용
	 
	//컨트롤러, 포인터 안 보임(사라진다)
	player->meshLeftHand->SetVisibility(false);
	player->meshRightHand->SetVisibility(false);
	player->compWidgetPointer_right->bShowDebug = false;

	//1초 페이드
	Fade(); 

	//0.5초 후 화면 캡처
	ClickScreenShot();

	if (ClickScreenShotBtn != false)
	{
		//1초 후 스크린샷 위젯, 컨트롤러 보임
		FTimerHandle WaitHandle;
		float WaitTime = 1.2f;
		currentWorld->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
			{
				//스크린샷 위젯이 보인다. 콜리전을	UI 로 한다
				player->SetWidgetActive(2, true); //------> 종섭님이 작업한 코드 사용

				//컨트롤러, 포인터 보임
				player->meshLeftHand->SetVisibility(true);
				player->meshRightHand->SetVisibility(true);
				player->compWidgetPointer_right->bShowDebug = true;
			}), WaitTime, false);
	}
}

//페이드
void URIM_Widget_ScreenShot::Fade()
{
	GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraFade(0, 0.5f, 0.5f, FLinearColor::Black);
}

//화면캡처 상세(딜레이, 페이드 등)
void URIM_Widget_ScreenShot::ClickScreenShot()
{
	//[0.5초 후 화면을 캡처한다]
	FTimerHandle WaitHandle;
	float WaitTime = 0.5f;
	currentWorld->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
		{
			player->TakeScreenShot(); //캡처 ------> 종섭님이 작업한 코드 사용
		}), WaitTime, false);

	//여유되면 찰칵 효과 추가한다

	ClickScreenShotBtn = true;
}

void URIM_Widget_ScreenShot::Close()
{
	//스크린샷 위젯이 안 보인다. 콜리전을 노콜리전으로 한다
	player->SetWidgetActive(2, false); //------> 종섭님이 작업한 코드 사용

	//왼손 메뉴 위젯이 보인다. 콜리전을 UI 로 한다
	player->SetWidgetActive(0, true); //------> 종섭님이 작업한 코드 사용
}