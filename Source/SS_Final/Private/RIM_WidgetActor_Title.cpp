// Fill out your copyright notice in the Description page of Project Settings.


#include "RIM_WidgetActor_Title.h"
#include <UMG/Public/Components/WidgetComponent.h>
#include <Kismet/GameplayStatics.h>
#include "RIM_Widget_Title.h"

// Sets default values
ARIM_WidgetActor_Title::ARIM_WidgetActor_Title()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//타이틀 위젯 추가
	widget_Title = CreateDefaultSubobject<UWidgetComponent>(TEXT("Title Widget Comp"));
	widget_Title->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void ARIM_WidgetActor_Title::BeginPlay()
{
	Super::BeginPlay();

	//액터의 함수를 위젯이 실행 할 수 있게 해주는 코드
	if (widget_Title != nullptr) //액터에 위젯이 있으면
	{
		URIM_Widget_Title* tempWidget = Cast<URIM_Widget_Title>(widget_Title->GetWidget());

		if (tempWidget != nullptr) //tempWidget 위젯이면
		{
			tempWidget->widgetActor_Title = this;
		}
	}
	

}

// Called every frame
void ARIM_WidgetActor_Title::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// [위젯에서 버튼을 클릭 했을 떄 실행 될 함수]
void ARIM_WidgetActor_Title::PlayStart()
{
	//SelectProject 레벨 열기
	//UGameplayStatics::OpenLevel(GetWorld(), "02_SelectProject");

	//NewMap 레벨 열기
	UGameplayStatics::OpenLevel(GetWorld(), "NewMap");

}

