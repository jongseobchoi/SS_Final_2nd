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

	//Ÿ��Ʋ ���� �߰�
	widget_Title = CreateDefaultSubobject<UWidgetComponent>(TEXT("Title Widget Comp"));
	widget_Title->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void ARIM_WidgetActor_Title::BeginPlay()
{
	Super::BeginPlay();

	//������ �Լ��� ������ ���� �� �� �ְ� ���ִ� �ڵ�
	if (widget_Title != nullptr) //���Ϳ� ������ ������
	{
		URIM_Widget_Title* tempWidget = Cast<URIM_Widget_Title>(widget_Title->GetWidget());

		if (tempWidget != nullptr) //tempWidget �����̸�
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


// [�������� ��ư�� Ŭ�� ���� �� ���� �� �Լ�]
void ARIM_WidgetActor_Title::PlayStart()
{
	//SelectProject ���� ����
	//UGameplayStatics::OpenLevel(GetWorld(), "02_SelectProject");

	//NewMap ���� ����
	UGameplayStatics::OpenLevel(GetWorld(), "NewMap");

}

